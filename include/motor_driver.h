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
 * @brief Stop both motors.
 *
 * This function disables motor movement.
 */
void motor_driver_stop(void);

/**
 * @brief Set speed for both motors in percent.
 *
 * @param percent Speed percentage from 0 to 100.
 */
void motor_driver_set_speed_percent(uint8_t percent);