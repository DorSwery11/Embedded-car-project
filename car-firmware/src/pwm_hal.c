#include "pwm_hal.h"
#include "driver/ledc.h"
#include "pins.h"


//pwm frequency && Resolution
#define PWM_FREQUENCY_HZ    20000U
#define PWM_MAX_DUTY        1023U

//private pwm configuration

#define PWM_SPEED_MODE         LEDC_LOW_SPEED_MODE
#define PWM_TIMER              LEDC_TIMER_0
#define PWM_DUTY_RESOLUTION    LEDC_TIMER_10_BIT

#define PWM_CHANNEL_A          LEDC_CHANNEL_0
#define PWM_CHANNEL_B          LEDC_CHANNEL_1


// static flag to check if the PWM already initialized
static bool initialized = 0;


esp_err_t pwm_hal_init(void)
{
    ledc_timer_config_t timer_config = {
            .speed_mode      = PWM_SPEED_MODE,
            .duty_resolution = PWM_DUTY_RESOLUTION,
            .timer_num       = PWM_TIMER,
            .freq_hz         = PWM_FREQUENCY_HZ,
            .clk_cfg         = LEDC_AUTO_CLK
    };
    esp_err_t result = ledc_timer_config(&timer_config);
    if(result != ESP_OK)
        return result;

    ledc_channel_config_t channel_a_config = {  //CHANNEL A CONFIG
    .gpio_num   = PIN_PWMA,
    .speed_mode = PWM_SPEED_MODE,
    .channel    = PWM_CHANNEL_A,
    .intr_type  = LEDC_INTR_DISABLE, // no interrupts for PWMA
    .timer_sel  = PWM_TIMER,  // PWM - A -> TIMER 0 
    .duty       = 0U,
    .hpoint     = 0
    };    

    result = ledc_channel_config(&channel_a_config);

    if (result != ESP_OK)
        return result;
    

    ledc_channel_config_t channel_b_config = {  //CHANNEL B CONFIG
    .gpio_num   = PIN_PWMB,
    .speed_mode = PWM_SPEED_MODE,
    .channel    = PWM_CHANNEL_B,
    .intr_type  = LEDC_INTR_DISABLE, // no interrupts for PWMB
    .timer_sel  = PWM_TIMER,  // PWM - B -> TIMER 0 
    .duty       = 0U,
    .hpoint     = 0
    };

    result = ledc_channel_config(&channel_b_config);
    if (result != ESP_OK)
        return result;
    initialized = 1;
    return ESP_OK;
}


esp_err_t pwm_hal_set_duty_percent(pwm_hal_output_t output,uint8_t percent){
    
    // INPUT VALIDATION
    if(percent >100U)
        return ESP_ERR_INVALID_ARG;
    if(!initialized)
        return ESP_ERR_INVALID_STATE;

    ledc_channel_t channel; // Current channel

    switch (output)  // protects HAL -> channel gets output (no directlly , for HAL can be safe)
    {
    case PWM_HAL_OUTPUT_A:
        channel = PWM_CHANNEL_A;
        break;

    case PWM_HAL_OUTPUT_B:
        channel = PWM_CHANNEL_B;
        break;
    default:
        return ESP_ERR_INVALID_ARG;
    }

        // PWM DUTY CYCLE CALCULATION
    uint32_t duty = ((uint32_t)percent * PWM_MAX_DUTY) / 100U;

    // Write the new duty value
    esp_err_t result = ledc_set_duty(PWM_SPEED_MODE,channel,duty);

    if (result != ESP_OK)
        return result;


    // Apply the new duty value to the hardware
    result = ledc_update_duty(PWM_SPEED_MODE,channel);
    if (result != ESP_OK)
        return result;

    return ESP_OK;


}


