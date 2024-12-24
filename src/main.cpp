#include <Arduino.h>
#include "ds3231.h"
#include "aht10.h"
#include "oled.h"
#include "alarm_buzzer.h"

// 定义 I2C 引脚
#define CUSTOM_SDA_PIN 16
#define CUSTOM_SCL_PIN 15

#define BUZZER_PIN 17

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

    alarm_buzzer_init(BUZZER_PIN);

        // 设置两个示例闹钟
    set_alarm(0, 7, 30, true, REPEATING); // 每天 7:30
    set_alarm(1, 8, 0, true, ONE_TIME);   // 一次性 8:00

    // 创建任务
    xTaskCreate(ds3231_task, "DS3231 Task", 4096, i2c_mutex, 2, NULL);
    xTaskCreate(aht10_task, "AHT10 Task", 4096, i2c_mutex, 1, NULL);
    xTaskCreate(oled_task, "OLED Task", 4096, NULL, 1, NULL);
    xTaskCreate(alarm_buzzer_task, "Alarm Buzzer Task", 2048, NULL, 1, NULL);
}

void loop() {
    // 串口动态设置闹钟
    if (Serial.available()) {
        char command[64];
        Serial.readBytesUntil('\n', command, sizeof(command));
        command[sizeof(command) - 1] = '\0';

        int index, hour, minute, enabled, type;
        if (sscanf(command, "SET %d %d %d %d %d", &index, &hour, &minute, &enabled, &type) == 5) {
            set_alarm(index, hour, minute, enabled, type == 0 ? REPEATING : ONE_TIME);
        } else if (sscanf(command, "DEL %d", &index) == 1) {
            delete_alarm(index);
        } else if (strcmp(command, "LIST") == 0) {
            list_alarms();
        } //else if () {

        //} 
        else {
            Serial.println("[Alarm] Invalid command. Use SET, DEL, or LIST.");
        }
    }
}
/*
格式：SET <index> <hour> <minute> <enabled> <type>
index：闹钟索引（从 0 开始）。
hour：闹钟小时。
minute：闹钟分钟。
enabled：1 表示启用，0 表示禁用。
type：0 表示重复闹钟，1 表示一次性闹钟。
*/