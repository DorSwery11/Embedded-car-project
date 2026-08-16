#include "pins.h"
#include "gpio_hal.h"
#include "pwm_hal.h"

static int initialized; 

esp_err_t motor_driver_init(void)
{
    if(initialized)
        return ESP_ERR_INVALID_STATE;
   
    // ENABLE STBY
    gpio_hal_init_output(PIN_STBY); // ENABLE STAND BY LEG
    gpio_hal_clear(PIN_STBY);         // Keep motor driver disabled during initialization
    
    // ENABLE A-IN
    gpio_hal_init_output(PIN_AIN1); // ENABLE SIDE A IN 1
    gpio_hal_init_output(PIN_AIN2); // ENABLE SIDE A IN 2

    // CLEAR A-SIDE
    gpio_hal_clear(PIN_AIN1);
    gpio_hal_clear(PIN_AIN2);

    // ENABLE B-IN
    gpio_hal_init_output(PIN_BIN1); // ENABLE SIDE B IN 1
    gpio_hal_init_output(PIN_BIN2); // ENABLE SIDE B IN 2

    // CLEAR B-SIDE
    gpio_hal_clear(PIN_BIN1);
    gpio_hal_clear(PIN_BIN2);

    //PWM init 
    esp_err_t init = pwm_hal_init();
    if(init != ESP_OK)
       return init;
    
    
    gpio_hal_set(PIN_STBY);   // Standby only HIGH if init successed 
    initialized = 1;  //flag of init is on
    return ESP_OK;
}
   
// static directions functions 
static void motor_driver_forward_A(void)
{
    // SET DIRECTION A - SIDE
    gpio_hal_set(PIN_AIN1);   // DIRECTION SIDE A        AIN1 = HIGH , AIN2 = LOW   -->> FORWARD A
    gpio_hal_clear(PIN_AIN2); // DIRECTION SIDE A
}
static void motor_driver_forward_B(void)
{
    // SET DIRECTION B - SIDE
    gpio_hal_clear(PIN_BIN1);   // DIRECTION SIDE B        BIN1 = LOW , BIN2 = HIGH   -->> FORWARD B
    gpio_hal_set(PIN_BIN2); // DIRECTION SIDE B
}
static void motor_driver_backward_A(void)
{
    // SET DIRECTION A - SIDE
    gpio_hal_clear(PIN_AIN1);   // DIRECTION SIDE A        AIN1 = LOW , AIN2 = HIGH   -->> BACKWARD A
    gpio_hal_set(PIN_AIN2); // DIRECTION SIDE A
}
static void motor_driver_backward_B(void)
{
    // SET DIRECTION B - SIDE
    gpio_hal_set(PIN_BIN1);   // DIRECTION SIDE B        BIN1 = HIGH , BIN2 = LOW   -->> BACKWARD B
    gpio_hal_clear(PIN_BIN2); // DIRECTION SIDE B
}

esp_err_t motor_driver_set_direction(motor_directiom side,int direction)


void motor_driver_stop(void)
{

}

void motor_driver_set_speed_percent(uint8_t percent)
{

}