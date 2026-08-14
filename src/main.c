#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "pins.h"
#include "motor_driver.h"


// static void motor_first_task(void *pvParameters)
// {
//     while(1){
//         // motor_driver_forward();
//         motor_driver_set_speed_percent(50);
//         vTaskDelay(pdMS_TO_TICKS(2000));
//         motor_driver_stop();
//         vTaskDelay(pdMS_TO_TICKS(2000));
//     }
// }



void app_main(void){
    motor_driver_init();
    // xTaskCreate(
    //     motor_first_task,  // motor bring up
    //     "motor_first_task",
    //     2048,
    //     NULL,
    //     5,
    //     NULL );
    motor_driver_forwardA();
    vTaskDelay(pdMS_TO_TICKS(100));
    motor_driver_backwardB();
    while(1){
       vTaskDelay(pdMS_TO_TICKS(40));
    }
}