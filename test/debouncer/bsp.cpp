#include "bsp.h"

static uint8_t fake_val = 0;
void bsp_pin_mode(uint8_t pin, uint8_t mode)
{
    ;
}
uint8_t bsp_digital_Read(uint8_t pin)
{
    return fake_val;
}

void bsp_set_fake_val(uint8_t val)
{
    fake_val =val;
}