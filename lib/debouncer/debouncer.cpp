#include "bsp.h"
#include "debouncer.h"
#include <stdint.h>
bool initialized = false;
uint8_t btn_pins_STATE[MAX_DEBOUNDER_PINS] = {0};
uint8_t btn_array[MAX_DEBOUNDER_PINS] = {0};
uint8_t btn_counter[MAX_DEBOUNDER_PINS] = {0};
uint8_t btn_edge[MAX_DEBOUNDER_PINS] = {0};

uint8_t btn_count = 0;
bool status = false;
static bool pin_number_inRange(uint8_t *pins, uint8_t pin_count)
{
    for (int i = 0; i < pin_count; i++)
    {
        if (pins[i] > DEBOUNCER_ARDINO_PIN)
        {
            return false;
        }
    }
    return true;
}
static bool pins_repeated(uint8_t *pins, uint8_t pin_count)
{
    for (int i = 0; i < pin_count; i++)
    {
        for (int j = i + 1; j < pin_count; j++)
        {
            if (pins[i] == pins[j])
            {
                return true;
            }
        }
    }
    return false;
}
uint8_t debouncer_init(uint8_t *pins, uint8_t pin_count)
{
    uint8_t result = DEBOUNCER_STATE_NOT_INITIALIZED;
    if (!pins)
    {
        result = DEBOUNCER_ERROR_INVALID_PIN_ARRAY;
    }
    else if (pin_count > MAX_DEBOUNDER_PINS)
    {
        result = DEBOUNCER_BUTTONS_TOO_MANY;
    }
    else if (pins_repeated(pins, pin_count))
    {
        result = DEBOUNCER_ERROR_DUPLICATED;
    }
    else if (!pin_number_inRange(pins, pin_count))
    {
        result = DEBOUNCER_ERROR_PIN_OUT_OF_RANGE;
    }
    else
    {
        if (pin_count <= MAX_DEBOUNDER_PINS)
        {
            for (uint8_t i = 0; i < pin_count; i++)
            {
                btn_array[i] = pins[i];
                btn_pins_STATE[i] = DEBOUNCER_STATE_HIGH;
                btn_edge[i] = DEBOUNCER_STATE_RISING;
                btn_counter[i] = 0;
            }
            btn_count = pin_count;
            initialized = true;
            result = DEBOUNCER_NO_ERROR;
        }
    }
    return result;
}
static void debouncer_update_btn(uint8_t index)
{

    uint8_t pin = btn_array[index];
    uint8_t pin_state = bsp_digital_Read(pin);
    if (pin_state == btn_pins_STATE[index])
    {
        btn_counter[index] = 0;
    }
    else
    {
        btn_counter[index]++;
        if (btn_counter[index] == DEBOUNCER_NO_RIPPLE)
        {
            btn_counter[index] = 0;

            if (btn_pins_STATE[index] == DEBOUNCER_STATE_LOW)
            {

                btn_edge[index] = DEBOUNCER_STATE_RISING;
                btn_pins_STATE[index] = DEBOUNCER_STATE_HIGH;
            }
            else
            {
                btn_edge[index] = DEBOUNCER_STATE_FALLING;
                btn_pins_STATE[index] = DEBOUNCER_STATE_LOW;
            }
        }
    }
}
void debouncer_update()
{
    if (initialized)
    {
        for (uint8_t i = 0; i < btn_count; i++)
        {
            debouncer_update_btn(i);
        }

        return;
    }
}

uint8_t debouncer_get_state(uint8_t pin)
{
    uint8_t result = DEBOUNCER_STATE_NOT_INITIALIZED;
    if (!initialized)
    {
        result = DEBOUNCER_STATE_NOT_INITIALIZED;
        return result;
    }
    else
    {
        for (int i = 0; i < sizeof(btn_array) / sizeof(btn_array[i]); i++)
        {
            if (pin == btn_array[i])
            {
                result = btn_pins_STATE[i];
                return result;
            }
        }
    }
    result = DEBOUNCER_ERROR_PIN_NOT_FOUND;
    return result;
}
uint8_t debouncer_get_edge(uint8_t pin)
{
    uint8_t result = DEBOUNCER_STATE_NOT_INITIALIZED;
    if (!initialized)
    {
        result = DEBOUNCER_STATE_NOT_INITIALIZED;
        return result;
    }
    else
    {
        for (int i = 0; i < sizeof(btn_array) / sizeof(btn_array[i]); i++)
        {
            if (pin == btn_array[i])
            {
                result = btn_edge[i];
                return result;
            }
        }
    }
    result = DEBOUNCER_ERROR_PIN_NOT_FOUND;
    return result;
}
