#ifndef GPIO_HAL_H
#define GPIO_HAL_H

#include <stdint.h>

void gpio_hal_init_output(uint8_t pin);
void gpio_hal_set(uint8_t pin);
void gpio_hal_clear(uint8_t pin);

#endif