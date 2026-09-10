#ifndef REMOTE_PINS_H
#define REMOTE_PINS_H

#include "driver/gpio.h"
#include "hal/adc_types.h"

/* Joystick wiring */
#define JOYSTICK_X_PIN            GPIO_NUM_34
#define JOYSTICK_Y_PIN            GPIO_NUM_35
#define JOYSTICK_SW_PIN           GPIO_NUM_15

/* ESP32 ADC1 channel mapping */
#define JOYSTICK_X_ADC_CHANNEL    ADC_CHANNEL_6
#define JOYSTICK_Y_ADC_CHANNEL    ADC_CHANNEL_7

#endif