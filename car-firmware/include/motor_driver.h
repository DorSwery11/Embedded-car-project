#pragma once

#include <stdint.h>
#include "esp_err.h"

typedef enum
{
    MOTOR_SIDE_LEFT = 0,
    MOTOR_SIDE_RIGHT
} motor_side_t;

typedef enum
{
    MOTOR_DIRECTION_FORWARD = 0,
    MOTOR_DIRECTION_BACKWARD
} motor_direction_t;


/**
 * @brief Initialize the motor driver GPIOs and PWM hardware.
 *
 * This function must be called once before using the motor driver.
 */
esp_err_t motor_driver_init(void);


esp_err_t motor_driver_set_direction(motor_side_t side,motor_direction_t direction);


/**
 * @brief Set the speed of the selected motor side in percent.
 *
 * @param side Motor side to control.
 * @param percent Speed percentage from 0 to 100.
 */
esp_err_t motor_driver_set_speed_percent(motor_side_t side, uint8_t percent);


/**
 * @brief Stop both motors.
 *
 * This function disables motor movement.
 */
esp_err_t motor_driver_stop(void);
