#include "pins.h"
#include <stdio.h>
#include "motor_driver.h"
#include "soc/gpio_reg.h"
#include "soc/gpio_struct.h"
#include "soc/io_mux_reg.h"
#include "soc/soc.h"

void motor_driver_init(void)
{
    // ENABLE STBY
    *(volatile uint32_t *)GPIO_ENABLE_W1TS_REG = (1UL << PIN_STBY); // ENABLE STAND BY LEG
    *(volatile uint32_t *)GPIO_OUT_W1TS_REG = (1UL << PIN_STBY);    // HIGH STAND BY

    // ENABLE A-IN
    *(volatile uint32_t *)GPIO_ENABLE_W1TS_REG = (1UL << PIN_AIN1); // ENABLE SIDE A IN 1
    *(volatile uint32_t *)GPIO_ENABLE_W1TS_REG = (1UL << PIN_AIN2); // ENABLE SIDE A IN 2

    // ENABLE B-IN
    *(volatile uint32_t *)GPIO_ENABLE_W1TS_REG = (1UL << PIN_BIN1); // ENABLE SIDE B IN 1
    *(volatile uint32_t *)GPIO_ENABLE_W1TS_REG = (1UL << PIN_BIN2); // ENABLE SIDE B IN 2

    //ENABLE PWM A - SIDE 
    *(volatile uint32_t *)GPIO_ENABLE_W1TS_REG = (1UL << PIN_PWMA); // ENABLE PWM A SIDE
    *(volatile uint32_t *)GPIO_OUT_W1TS_REG = (1UL << PIN_PWMA);    // HIGH PWM A SIDE
  
    //ENABLE PWM B - SIDE 
    *(volatile uint32_t *)GPIO_ENABLE_W1TS_REG = (1UL << PIN_PWMB); // ENABLE PWM B SIDE
    *(volatile uint32_t *)GPIO_OUT_W1TS_REG = (1UL << PIN_PWMB);    // HIGH PWM B SIDE
}

void motor_driver_forwardA(void)
{
    // SET DIRECTION A - SIDE
    *(volatile uint32_t *)GPIO_OUT_W1TS_REG = (1UL << PIN_AIN1); // DIERCTION SIDE A
    *(volatile uint32_t *)GPIO_OUT_W1TC_REG = (1UL << PIN_AIN2); // DIERCTION SIDE A

}
void motor_driver_forwardB(void)
{    
    // SET DIRECTION B - SIDE
    *(volatile uint32_t *)GPIO_OUT_W1TC_REG = (1UL << PIN_BIN1); // DIERCTION SIDE B
    *(volatile uint32_t *)GPIO_OUT_W1TS_REG = (1UL << PIN_BIN2); // DIERCTION SIDE B

}
void motor_driver_stop(void)
{
    printf("motor_driver_stop()\n");
}

void motor_driver_set_speed_percent(uint8_t percent)
{
    printf("motor_driver_set_speed_percent(%u)\n", percent);
}