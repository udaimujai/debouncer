#ifndef DEBOUNCER_H
#define DEBOUNCER_H
#include <stdint.h> 
#define DEBOUNCER_ERROR_OK true
#define MAX_DEBOUNDER_PINS 8
#define DEBOUNCER_ARDINO_PIN 57

#define DEBOUNCER_ERROR_INVALID_PIN_ARRAY 1 // the buttons array cannot be empty.
#define DEBOUNCER_BUTTONS_TOO_MANY 2
#define DEBOUNCER_ERROR_DUPLICATED 3 // duplicate pins specified.
#define DEBOUNCER_ERROR_PIN_OUT_OF_RANGE 4
#define DEBOUNCER_ERROR_NOT_INITIALIZED 5//the function debounce_init MUST be called before calling debouncer_get_state();
#define DEBOUNCER_NO_ERROR 6
#define DEBOUNCER_STATE_NOT_INITIALIZED 7
#define DEBOUNCER_ERROR_PIN_NOT_FOUND 8

#define DEBOUNCER_STATE_HIGH 1
#define DEBOUNCER_STATE_LOW 0
#define DEBOUNCER_STATE_RISING 2
#define DEBOUNCER_STATE_FALLING 3
#define DEBOUNCER_NO_RIPPLE 5 //threshold number to decide no ripple in the input signal when button pressed
uint8_t debouncer_init(uint8_t *pins, uint8_t pin_count);
/**
 * @brief update the status of all the pins requested for debouncer.
 * 
 */
void debouncer_update();
/**
 * @brief Get the state of a specific pin to hte debouncer.
 * 
 * @param pin pin number
 * @return uint8_t returns statusof the pin of error codes.
 */
uint8_t debouncer_get_state(uint8_t pin);
#endif
