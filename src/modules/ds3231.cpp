#include "ds3231.h"

// RTC 实例
RTC_DS3231 rtc;

extern SemaphoreHandle_t aht10_signal; // 声明信号量

// DS3231 初始化函数
void ds3231_init() {
    if (!rtc.begin()) {
        Serial.println("[DS3231] Initialization failed.");
        return;
    }

    // 检查是否丢失电源，如果是则设置默认时间
    if (rtc.lostPower()) {
        Serial.println("[DS3231] Lost power, resetting time.");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // 设置为编译时间
    }
}

// DS3231 任务函数
void ds3231_task(void *parameter) {
    if (parameter == NULL) {
        Serial.println("[DS3231] Invalid parameter passed to task.");
        vTaskDelete(NULL);
    }

    ds3231_init(); // 初始化 DS3231

    SemaphoreHandle_t i2c_mutex = (SemaphoreHandle_t)parameter;

    while (true) {
        if (xSemaphoreTake(i2c_mutex, portMAX_DELAY)) { // 获取 I2C 互斥锁
            // 读取时间
            DateTime now = rtc.now();

            if (now.isValid()) { // 检查读取时间的有效性
                Serial.printf("[DS3231] Time: %02d/%02d/%02d %02d:%02d\n", 
                              now.year() % 100, now.month(), now.day(), now.hour(), now.minute());
                xSemaphoreGive(aht10_signal); // 发送信号
            } else {
                Serial.println("[DS3231] Invalid time data.");
            }

            xSemaphoreGive(i2c_mutex); // 释放 I2C 互斥锁
        } else {
            Serial.println("[DS3231] Failed to acquire I2C mutex.");
        }

        vTaskDelay(600000 / portTICK_PERIOD_MS); // 每秒输出一次时间
    }
}
