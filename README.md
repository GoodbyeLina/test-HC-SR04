# ESP32-S3 HC-SR04超声波测距项目

本项目实现了ESP32-S3开发板驱动HC-SR04超声波传感器进行距离测量的功能。

## 功能特性
- 使用ESP-IDF开发框架
- 通过HC-SR04超声波传感器测量距离
- 每秒输出一次测量结果(厘米)
- 支持串口输出测量数据

## 硬件连接
| HC-SR04引脚 | ESP32-S3 GPIO |
|------------|--------------|
| VCC        | 3.3V         |
| GND        | GND          |
| Trig       | GPIO15       |
| Echo       | GPIO16       |

## 使用说明
1. 按照上表连接硬件
2. 编译并烧录程序：
   ```bash
   idf.py build
   idf.py flash
   ```
3. 查看串口输出：
   ```bash
   idf.py monitor
   ```

## 项目结构
```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   └── main.c          # 主程序文件
└── README.md           # 项目说明文件
```

## 注意事项
- 确保Trig和Echo引脚连接正确
- 测量范围: 2cm-400cm
- 测量精度: ±3mm
They are not used or needed when building with CMake and idf.py.
