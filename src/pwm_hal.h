#pragma once
#include <stdint.h>
#include "esp_err.h"



typedef enum
{
    PWM_HAL_OUTPUT_A = 0,
    PWM_HAL_OUTPUT_B

} pwm_hal_output_t;

esp_err_t pwm_hal_init(void);
esp_err_t pwm_hal_set_duty_percent(pwm_hal_output_t output,uint8_t percent);