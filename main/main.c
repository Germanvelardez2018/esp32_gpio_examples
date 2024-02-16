
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/gptimer.h"
#include "esp_timer.h"

#define LED_GPIO_ESP32      2


uint64_t time = 0 ;
bool toggle = false;

void timer_cb(void*){
        toggle = (toggle  == true)?     false:    true;
        gpio_set_level(LED_GPIO_ESP32, toggle);
}

static esp_timer_create_args_t cfg = {.callback = timer_cb,
                                      .arg  = NULL,
                                      .name = "TIMER A",
                                      .dispatch_method = ESP_TIMER_TASK,
                                      .skip_unhandled_events = true};
static esp_timer_handle_t timerA ;


void app_main(void)
{
    // Create a timer
    esp_err_t ret;
    gpio_set_direction(LED_GPIO_ESP32,GPIO_MODE_DEF_OUTPUT);
    printf("Init esp32\r\n");

    ret = esp_timer_create(&cfg,&timerA);
    if(ret != ESP_OK)printf("Error al iniciar el timer \r\n");
    ret = esp_timer_start_periodic(timerA,1000000);
    if(ret != ESP_OK)printf("Error al iniciar el timer \r\n");
    
    uint64_t base = esp_timer_get_time();
    for (int i = 0; i <= 200; i++) {
         
          vTaskDelay(1000 / portTICK_PERIOD_MS);
         
          time = esp_timer_get_time();
          printf("  Counter = %lld  seconds...\r\n", ((time-base)/1000000));

        }

    esp_restart();

}