#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hc_sr04.h"

void app_main(void)
{
    // 初始化HC-SR04
    hc_sr04_config_t config = {
        .trig_pin = GPIO_NUM_15,
        .echo_pin = GPIO_NUM_16
    };
    esp_err_t ret = hc_sr04_init(&config);
    if (ret != ESP_OK) {
        printf("HC-SR04 init failed: %d\n", ret);
        return;
    }

    while(1) {
        float distance = hc_sr04_measure_distance();
        if (distance >= 0) {
            printf("Distance: %.2f cm\n", distance);
        } else {
            printf("Measurement failed\n");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
