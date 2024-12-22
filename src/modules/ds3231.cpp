#include "ds3231.h"

// 创建全局 DS3231 实例
RTC_DS3231 rtc;

// 信号量（由 main.cpp 中初始化）
extern SemaphoreHandle_t aht10_signal;

void ds3231_init(int sdaPin, int sclPin) {
    Wire.begin(sdaPin, sclPin);
    Wire.setClock(100000); // 设置 I2C 频率为 100kHz

    if (!rtc.begin()) {
        Serial.println("[DS3231] Initialization failed.");
        return;
    }

    if (rtc.lostPower()) {
        Serial.println("[DS3231] Lost power, resetting time.");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // 设置为编译时间
    }

    Serial.println("[DS3231] Initialization successful.");
}

void ds3231_task(void *parameter) {
    SemaphoreHandle_t i2c_mutex = (SemaphoreHandle_t)parameter;

    while (true) {
        if (xSemaphoreTake(i2c_mutex, portMAX_DELAY)) { // 获取 I2C 互斥锁
            DateTime now = rtc.now();

            if (now.isValid()) { // 检查时间是否有效
                Serial.printf("[DS3231] Time: %02d/%02d/%02d %02d:%02d\n", 
                              now.year() % 100, now.month(), now.day(), now.hour(), now.minute());

                // 通知 AHT10 任务
                xSemaphoreGive(aht10_signal);
            } else {
                Serial.println("[DS3231] Failed to read time.");
            }

            xSemaphoreGive(i2c_mutex); // 释放 I2C 互斥锁
        } else {
            Serial.println("[DS3231] Failed to acquire I2C mutex.");
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS); // 每秒运行一次
    }
}
