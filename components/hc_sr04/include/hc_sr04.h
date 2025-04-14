#ifndef HC_SR04_H
#define HC_SR04_H

#include "driver/gpio.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief HC-SR04 传感器配置结构体
 */
typedef struct {
    gpio_num_t trig_pin;  // Trig引脚
    gpio_num_t echo_pin;  // Echo引脚
} hc_sr04_config_t;

/**
 * @brief 初始化HC-SR04传感器
 * @param config 传感器配置参数
 * @return esp_err_t 
 */
esp_err_t hc_sr04_init(const hc_sr04_config_t *config);

/**
 * @brief 测量距离(厘米)
 * @return float 距离值(厘米)，测量失败返回-1
 */
float hc_sr04_measure_distance(void);

#ifdef __cplusplus
}
#endif

#endif // HC_SR04_H
