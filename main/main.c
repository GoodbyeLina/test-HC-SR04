#include <stdio.h>
#include "driver/gpio.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// 简单的微秒延时函数
static void delay_us(uint32_t us) {
    uint32_t cycles = us * (CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ);
    volatile uint32_t count = 0;
    for(; count < cycles; count++);
}

#define TRIG_GPIO 15
#define ECHO_GPIO 16

float measure_distance() {
    // 发送10us的Trig脉冲
    gpio_set_level(TRIG_GPIO, 0);
    delay_us(2);
    gpio_set_level(TRIG_GPIO, 1);
    delay_us(10);
    gpio_set_level(TRIG_GPIO, 0);

    // 等待Echo高电平开始
    while(gpio_get_level(ECHO_GPIO) == 0);
    int64_t start = esp_timer_get_time();

    // 等待Echo高电平结束
    while(gpio_get_level(ECHO_GPIO) == 1);
    int64_t end = esp_timer_get_time();

    // 计算距离(cm) = (高电平时间(us) / 58
    return (end - start) / 58.0;
}

void app_main(void)
{
    // 初始化GPIO
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << TRIG_GPIO),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    io_conf.pin_bit_mask = (1ULL << ECHO_GPIO);
    io_conf.mode = GPIO_MODE_INPUT;
    gpio_config(&io_conf);

    while(1) {
        float distance = measure_distance();
        printf("Distance: %.2f cm\n", distance);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}