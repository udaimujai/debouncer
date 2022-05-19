#ifndef BSP_H
#define BSP_H
#include <stdint.h>
uint8_t bsp_digital_Read(uint8_t pin);
//sets value for testing
void bsp_set_fake_val(uint8_t val);
#endif