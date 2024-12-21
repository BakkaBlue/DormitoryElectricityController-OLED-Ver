#ifndef AHT10_H
#define AHT10_H

#include "AHT10.h"
#include <Adafruit_AHTX0.h>
#include <Wire.h>

// 定义 AHT10 I2C 引脚
#define AHT10_SDA 16
#define AHT10_SCL 15

// 初始化 AHT10 传感器（支持自定义引脚）
bool aht10_init(int sdaPin = -1, int sclPin = -1);                   // 初始化 AHT10
bool aht10_read(float &temperature, float &humidity); // 读取温湿度数据

#endif

