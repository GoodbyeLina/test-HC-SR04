# ESP32-S3 HC-SR04超声波传感器驱动库

这是一个通用的HC-SR04超声波传感器驱动库，适用于ESP32-S3开发板。

## 功能特性
- 模块化设计，可作为独立组件使用
- 可配置任意GPIO引脚
- 精确的距离测量(厘米)
- 完善的错误处理机制
- 支持ESP-IDF开发框架

## 安装使用

1. 将`components/hc_sr04`目录复制到您的项目
2. 在项目CMakeLists.txt中添加：
   ```cmake
   list(APPEND EXTRA_COMPONENT_DIRS components)
   ```
3. 在代码中包含头文件：
   ```c
   #include "hc_sr04.h"
   ```

## API文档

### 初始化
```c
hc_sr04_config_t config = {
    .trig_pin = GPIO_NUM_X,  // 设置Trig引脚
    .echo_pin = GPIO_NUM_Y   // 设置Echo引脚
};
esp_err_t ret = hc_sr04_init(&config);
```

### 测量距离
```c
float distance = hc_sr04_measure_distance();
// 返回距离(厘米)，失败返回-1
```

## 示例项目

```c
#include "hc_sr04.h"

void app_main() {
    hc_sr04_config_t config = {
        .trig_pin = GPIO_NUM_15,
        .echo_pin = GPIO_NUM_16
    };
    hc_sr04_init(&config);

    while(1) {
        float distance = hc_sr04_measure_distance();
        printf("Distance: %.2f cm\n", distance);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
```

## 项目结构
```
├── components
│   └── hc_sr04         # 驱动组件
│       ├── include     # 头文件
│       ├── src         # 源文件
│       └── CMakeLists.txt
├── example             # 示例代码
│   ├── CMakeLists.txt
│   └── main.c
└── README.md
```

## 注意事项
- 测量范围: 2cm-400cm
- 测量精度: ±3mm
- 建议Trig和Echo引脚之间保持一定距离
- 确保供电电压为3.3V
