#include "gpio_hal.h"
#include "soc/gpio_reg.h"
#include "soc/soc.h"

// Set GPIO as output

void gpio_hal_init_output(uint8_t pin)
{
    *(volatile uint32_t *)GPIO_ENABLE_W1TS_REG = (1U << pin);
}

// set GPIO to HIGH

void gpio_hal_set(uint8_t pin)
{
    *(volatile uint32_t *)GPIO_OUT_W1TS_REG = (1U << pin);
}

// set GPIO to LOW

void gpio_hal_clear(uint8_t pin)
{
    *(volatile uint32_t *)GPIO_OUT_W1TC_REG = (1U << pin);
}