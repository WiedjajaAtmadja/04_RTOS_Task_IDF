#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_RED   21
#define LED_GREEN 22
#define LED_BLUE  23

void taskBlinkRed(void *param) {
    esp_rom_gpio_pad_select_gpio(LED_RED);
    gpio_set_direction(LED_RED, GPIO_MODE_OUTPUT);

    while (1) {
        gpio_set_level(LED_RED, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
        gpio_set_level(LED_RED, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
    }
}

void taskBlinkGreen(void *param) {
    esp_rom_gpio_pad_select_gpio(LED_GREEN);
    gpio_set_direction(LED_GREEN, GPIO_MODE_OUTPUT);

    while (1) {
        gpio_set_level(LED_GREEN, 1);
        vTaskDelay(300 / portTICK_PERIOD_MS); // Delay for 300 ms
        gpio_set_level(LED_GREEN, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
    }
}
void app_main() {
    esp_rom_gpio_pad_select_gpio(LED_BLUE);
    gpio_set_direction(LED_BLUE, GPIO_MODE_OUTPUT);
    xTaskCreatePinnedToCore(taskBlinkRed, "blink_red", configMINIMAL_STACK_SIZE, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(taskBlinkGreen, "blink_green", configMINIMAL_STACK_SIZE, NULL, 1, NULL, 1);
    while(1)
    {
        gpio_set_level(LED_BLUE, 1);
        vTaskDelay(300 / portTICK_PERIOD_MS); // Delay for 300 ms
        gpio_set_level(LED_BLUE, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
    }
}