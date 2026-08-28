#include "pins.h"
#include "gpio_hal.h"
#include "pwm_hal.h"
#include "motor_driver.h"

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


// LEFT SIDE 
static void motor_driver_forward_a(void)
{
    // SET DIRECTION A - SIDE
    gpio_hal_set(PIN_AIN1);   // DIRECTION SIDE A        AIN1 = HIGH , AIN2 = LOW   -->> FORWARD A
    gpio_hal_clear(PIN_AIN2); // DIRECTION SIDE A
}
static void motor_driver_backward_a(void)
{
    // SET DIRECTION A - SIDE
    gpio_hal_clear(PIN_AIN1);   // DIRECTION SIDE A        AIN1 = LOW , AIN2 = HIGH   -->> BACKWARD A
    gpio_hal_set(PIN_AIN2); // DIRECTION SIDE A
}


//RIGHT SIDE
static void motor_driver_forward_b(void)
{
    // SET DIRECTION B - SIDE
    gpio_hal_clear(PIN_BIN1);   // DIRECTION SIDE B        BIN1 = LOW , BIN2 = HIGH   -->> FORWARD B
    gpio_hal_set(PIN_BIN2); // DIRECTION SIDE B
}

static void motor_driver_backward_b(void)
{
    // SET DIRECTION B - SIDE
    gpio_hal_set(PIN_BIN1);   // DIRECTION SIDE B        BIN1 = HIGH , BIN2 = LOW   -->> BACKWARD B
    gpio_hal_clear(PIN_BIN2); // DIRECTION SIDE B
}



esp_err_t motor_driver_set_direction(motor_side_t side,motor_direction_t direction)
{
    //input validation
    if(!initialized)
        return ESP_ERR_INVALID_STATE;
    if(side != MOTOR_SIDE_LEFT && side != MOTOR_SIDE_RIGHT)
        return ESP_ERR_INVALID_ARG;
    if(direction != MOTOR_DIRECTION_BACKWARD && direction != MOTOR_DIRECTION_FORWARD)
        return ESP_ERR_INVALID_ARG;


   switch(side)
   {
        case MOTOR_SIDE_LEFT:
            if(direction == MOTOR_DIRECTION_BACKWARD)
                motor_driver_backward_a();
            else
                motor_driver_forward_a();
            break;
        case MOTOR_SIDE_RIGHT:
            if(direction == MOTOR_DIRECTION_BACKWARD)
                motor_driver_backward_b();
            else
                motor_driver_forward_b();
            break;
   }

   return ESP_OK;
}


esp_err_t motor_driver_set_speed_percent(motor_side_t side, uint8_t percent)
{
    //input validation
     if(!initialized)
        return ESP_ERR_INVALID_STATE;

    if(side != MOTOR_SIDE_LEFT && side != MOTOR_SIDE_RIGHT)
        return ESP_ERR_INVALID_ARG;
    
    if(percent > 100)
        return ESP_ERR_INVALID_ARG;

    esp_err_t result = ESP_ERR_INVALID_ARG;
    switch (side)
    {
    case MOTOR_SIDE_LEFT:
        result = pwm_hal_set_duty_percent(PWM_HAL_OUTPUT_A,percent);
        break;
    case MOTOR_SIDE_RIGHT:
        result = pwm_hal_set_duty_percent(PWM_HAL_OUTPUT_B,percent);
        break;
    }
    return result;
}

esp_err_t motor_driver_stop(void)
{
    //input validation
     if(!initialized)
        return ESP_ERR_INVALID_STATE;

    esp_err_t result_left = ESP_ERR_INVALID_ARG;
    esp_err_t result_right = ESP_ERR_INVALID_ARG;

    result_left = motor_driver_set_speed_percent(MOTOR_SIDE_LEFT,0);
    result_right = motor_driver_set_speed_percent(MOTOR_SIDE_RIGHT,0);
    if(result_left == ESP_OK && result_right == ESP_OK)
        return ESP_OK;
    else if(result_left != ESP_OK)
        return result_left;
    return result_right;
}