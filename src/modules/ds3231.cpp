#include "ds3231.h"

// RTC 实例
RTC_DS3231 rtc;

// DS3231 初始化函数
void ds3231_init() {
    if (!rtc.begin()) {
        Serial.println("Failed to initialize DS3231!");
        return;
    }

    // 检查是否丢失电源，如果是则设置默认时间
    if (rtc.lostPower()) {
        Serial.println("DS3231 lost power, setting default time!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // 设置为编译时间
    }
}

// DS3231 任务函数
void ds3231_task(void *parameter) {
    while (true) {
        DateTime now = rtc.now();
        Serial.printf("Time: %02d/%02d/%02d %02d:%02d\n", 
                      now.year() % 100, now.month(), now.day(), now.hour(), now.minute());
        vTaskDelay(30000 / portTICK_PERIOD_MS); // 每分输出一次时间
    }
}
