#ifndef AHT10_H
#define AHT10_H

#include <Arduino.h>
#include "AHT10.h"
#include <Adafruit_AHTX0.h>

// 定义 AHT10 I2C 引脚
#define AHT10_SDA 16
#define AHT10_SCL 15

// 函数声明
bool aht10_initial();                      // 初始化 AHT10
bool aht10_number_read(float *temperature, float *humidity); // 读取温湿度数据

#endif

