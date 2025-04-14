#include "hc_sr04.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static gpio_num_t trig_pin = 0;
static gpio_num_t echo_pin = 0;

// 微秒延时函数
static void delay_us(uint32_t us) {
    uint64_t start = esp_timer_get_time();
    while (esp_timer_get_time() - start < us);
}

esp_err_t hc_sr04_init(const hc_sr04_config_t *config) {
    if (!config) return ESP_ERR_INVALID_ARG;

    trig_pin = config->trig_pin;
    echo_pin = config->echo_pin;

    // 初始化Trig引脚(输出)
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << trig_pin),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    esp_err_t ret = gpio_config(&io_conf);
    if (ret != ESP_OK) return ret;

    // 初始化Echo引脚(输入)
    io_conf.pin_bit_mask = (1ULL << echo_pin);
    io_conf.mode = GPIO_MODE_INPUT;
    return gpio_config(&io_conf);
}

float hc_sr04_measure_distance(void) {
    if (trig_pin == 0 || echo_pin == 0) return -1;

    // 发送10us的Trig脉冲
    gpio_set_level(trig_pin, 0);
    delay_us(2);
    gpio_set_level(trig_pin, 1);
    delay_us(10);
    gpio_set_level(trig_pin, 0);

    // 等待Echo高电平开始
    while(gpio_get_level(echo_pin) == 0);
    int64_t start = esp_timer_get_time();

    // 等待Echo高电平结束
    while(gpio_get_level(echo_pin) == 1);
    int64_t end = esp_timer_get_time();

    // 计算距离(cm) = (高电平时间(us) / 58
    return (end - start) / 58.0;
}
