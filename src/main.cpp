#include <Arduino.h>
#include "ds3231.h"
#include "aht10.h"
#include "oled.h"

// 定义 I2C 引脚
#define CUSTOM_SDA_PIN 16
#define CUSTOM_SCL_PIN 15

// 全局信号量和互斥锁
SemaphoreHandle_t i2c_mutex;
SemaphoreHandle_t aht10_signal;

// 全局共享变量
char current_time[16] = "00:00";
char current_date[16] = "0000/00/00";
char current_temp_hum[32] = "Temp: --.-C Hum: --.-%";

void setup() {
    Serial.begin(115200);

    // 初始化 I2C 互斥锁
    i2c_mutex = xSemaphoreCreateMutex();
    if (i2c_mutex == NULL) {
        Serial.println("[Setup] Failed to create I2C mutex.");
        while (1);
    }

    // 初始化信号量
    aht10_signal = xSemaphoreCreateBinary();
    if (aht10_signal == NULL) {
        Serial.println("[Setup] Failed to create signal.");
        while (1);
    }

    // 按顺序初始化设备
    ds3231_init(CUSTOM_SDA_PIN, CUSTOM_SCL_PIN);
    if (!aht10_init(CUSTOM_SDA_PIN, CUSTOM_SCL_PIN)) {
        Serial.println("[Setup] Failed to initialize AHT10.");
    }
    if (!oled_init(CUSTOM_SDA_PIN, CUSTOM_SCL_PIN)) {
        Serial.println("[Setup] Failed to initialize OLED.");
    }

    // 创建任务
    xTaskCreate(ds3231_task, "DS3231 Task", 4096, i2c_mutex, 2, NULL);
    xTaskCreate(aht10_task, "AHT10 Task", 4096, i2c_mutex, 1, NULL);
    xTaskCreate(oled_task, "OLED Task", 4096, NULL, 1, NULL);
}

void loop() {
    //Mr.Cyren
}
