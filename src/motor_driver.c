#include "pins.h"
#include "gpio_hal.h"
#include "pwm_hal.h"

void motor_driver_init(void)
{
    // ENABLE STBY
    gpio_hal_init_output(PIN_STBY); // ENABLE STAND BY LEG
    gpio_hal_clear(PIN_STBY);         // HIGH STAND BY

    // ENABLE A-IN
    gpio_hal_init_output(PIN_AIN1); // ENABLE SIDE A IN 1
    gpio_hal_init_output(PIN_AIN2); // ENABLE SIDE A IN 2

    // ENABLE B-IN
    gpio_hal_init_output(PIN_BIN1); // ENABLE SIDE B IN 1
    gpio_hal_init_output(PIN_BIN2); // ENABLE SIDE B IN 2

    // // ENABLE PWM A - SIDE
    // gpio_hal_init_output(PIN_PWMA); // ENABLE PWM A SIDE
    // gpio_hal_set(PIN_PWMA); // ENABLE PWM A SIDE


    // // ENABLE PWM B - SIDE
    // gpio_hal_init_output(PIN_PWMB); // ENABLE PWM B SIDE
    // gpio_hal_set(PIN_PWMB); // ENABLE PWM A SIDE
    esp_err_t init = pwm_hal_init();
    if(init != ESP_OK)
        return;
    gpio_hal_set(PIN_STBY);  // Standby only HIGH if init successed 
    pwm_hal_set_duty_percent(PWM_HAL_OUTPUT_A,80);
    pwm_hal_set_duty_percent(PWM_HAL_OUTPUT_B,80);


}

void motor_driver_forwardA(void)
{
    // SET DIRECTION A - SIDE
    gpio_hal_set(PIN_AIN1);   // DIRECTION SIDE A        AIN1 = HIGH , AIN2 = LOW   -->> FORWARD A
    gpio_hal_clear(PIN_AIN2); // DIRECTION SIDE A
}
void motor_driver_forwardB(void)
{
    // SET DIRECTION B - SIDE
    gpio_hal_clear(PIN_BIN1);   // DIRECTION SIDE B        BIN1 = LOW , BIN2 = HIGH   -->> FORWARD B
    gpio_hal_set(PIN_BIN2); // DIRECTION SIDE B
}
void motor_driver_backwardA(void)
{
    // SET DIRECTION A - SIDE
    gpio_hal_clear(PIN_AIN1);   // DIRECTION SIDE A        AIN1 = LOW , AIN2 = HIGH   -->> BACKWARD A
    gpio_hal_set(PIN_AIN2); // DIRECTION SIDE A
}
void motor_driver_backwardB(void)
{
    // SET DIRECTION B - SIDE
    gpio_hal_set(PIN_BIN1);   // DIRECTION SIDE B        BIN1 = HIGH , BIN2 = LOW   -->> BACKWARD B
    gpio_hal_clear(PIN_BIN2); // DIRECTION SIDE B
}
void motor_driver_stop(void)
{

}

void motor_driver_set_speed_percent(uint8_t percent)
{

}