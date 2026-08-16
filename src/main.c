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
    esp_err_t res = motor_driver_init();
    if(res != ESP_OK) return;
    // xTaskCreate(
    //     motor_first_task,  // motor bring up
    //     "motor_first_task",
    //     2048,
    //     NULL,
    //     5,
    //     NULL );
    motor_driver_set_direction(MOTOR_SIDE_LEFT,MOTOR_DIRECTION_FORWARD);
    motor_driver_set_direction(MOTOR_SIDE_RIGHT,MOTOR_DIRECTION_FORWARD);
    motor_driver_set_speed_percent(MOTOR_SIDE_LEFT,90);
    vTaskDelay(pdMS_TO_TICKS(100));
    motor_driver_set_speed_percent(MOTOR_SIDE_RIGHT,40);
    while(1){
       vTaskDelay(pdMS_TO_TICKS(40));
    }
}