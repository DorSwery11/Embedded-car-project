#pragma once

#include <stdint.h>

/**
 * @brief Initialize the motor driver GPIOs and PWM hardware.
 *
 * This function must be called once before using the motor driver.
 */
void motor_driver_init(void);

/**
 * @brief Drive both motors forward.
 *
 * This function only sets the motor direction.
 * Speed is controlled separately by motor_driver_set_speed_percent().
 */
void motor_driver_forwardA(void);
void motor_driver_forwardB(void);
void motor_driver_backwardA(void);
void motor_driver_backwardB(void);


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