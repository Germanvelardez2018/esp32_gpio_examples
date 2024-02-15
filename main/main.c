
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_GPIO_ESP32      2



void app_main(void)
{
    gpio_set_direction(LED_GPIO_ESP32,GPIO_MODE_DEF_OUTPUT);
    printf("Init esp32\r\n");
    bool toggle = false;
    for (int i = 200; i >= 0; i--) {
            printf("Restarting in %d seconds...\n", i);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            toggle = (toggle  == true)?     false:    true;
            gpio_set_level(LED_GPIO_ESP32, toggle);

        }

    esp_restart();

}