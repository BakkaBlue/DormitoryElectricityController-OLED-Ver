#include "alarm_buzzer.h"
#include "ds3231.h" // 引用全局时间变量

// 引用全局时间和日期变量
extern char current_time[16];
extern char current_date[16];

extern RTC_DS3231 rtc;

// 全局变量
Alarm alarms[MAX_ALARMS];
int buzzer_pin = -1;

// 初始化闹钟模块
void alarm_buzzer_init(int buzzerPin) {
    buzzer_pin = buzzerPin;
    pinMode(buzzer_pin, OUTPUT);
    digitalWrite(buzzer_pin, HIGH);

    for (int i = 0; i < MAX_ALARMS; i++) {
        alarms[i].hour = 0;
        alarms[i].minute = 0;
        alarms[i].enabled = false;
        alarms[i].type = REPEATING;
    }

    Serial.println("[Alarm] Alarm module initialized.");
}

bool set_alarm(int index, int hour, int minute, bool enabled, AlarmType type) {
    if (index < 0 || index >= MAX_ALARMS) {
        Serial.printf("[Alarm] Invalid alarm index: %d\n", index);
        return false; // 索引无效
    }

    alarms[index].hour = hour;
    alarms[index].minute = minute;
    alarms[index].enabled = enabled;
    alarms[index].type = type;

    Serial.printf("[Alarm] Alarm %d set to %02d:%02d, Enabled: %d, Type: %s\n",
                  index, hour, minute, enabled, type == REPEATING ? "Repeating" : "One-Time");
    return true;
}

bool delete_alarm(int index) {
    if (index < 0 || index >= MAX_ALARMS) {
        Serial.printf("[Alarm] Invalid alarm index: %d\n", index);
        return false; // 索引无效
    }

    alarms[index].enabled = false;
    alarms[index].hour = 0;
    alarms[index].minute = 0;
    alarms[index].type = REPEATING;

    Serial.printf("[Alarm] Alarm %d deleted.\n", index);
    return true;
}

void list_alarms() {
    Serial.println("[Alarm] Current alarm list:");
    for (int i = 0; i < MAX_ALARMS; i++) {
        Serial.printf("  Alarm %d: %02d:%02d, Enabled: %d, Type: %s\n",
                      i, alarms[i].hour, alarms[i].minute, alarms[i].enabled,
                      alarms[i].type == REPEATING ? "Repeating" : "One-Time");
    }
}

// 闹钟任务
void alarm_buzzer_task(void *parameter) {
    while (true) {
        // 从 DS3231 获取当前时间
        DateTime now = rtc.now();

        if (now.isValid()) {
            for (int i = 0; i < MAX_ALARMS; i++) {
                // 检查闹钟是否匹配当前时间
                if (alarms[i].enabled &&
                    alarms[i].hour == now.hour() &&
                    alarms[i].minute == now.minute() &&
                    now.second() == 0) { // 每分钟第 0 秒触发
                    Serial.printf("[Alarm] Alarm %d triggered at %02d:%02d\n", i, now.hour(), now.minute());

                    // 发出急促四声闹铃
                    for (int j = 0; j < 4; j++) {
                        digitalWrite(buzzer_pin, LOW);  // 低电平触发
                        delay(200);                    // 响 200ms
                        digitalWrite(buzzer_pin, HIGH); // 关闭
                        delay(200);                    // 停 200ms
                    }

                    // 如果是一次性闹钟，触发后禁用
                    if (alarms[i].type == ONE_TIME) {
                        alarms[i].enabled = false;
                        Serial.printf("[Alarm] Alarm %d disabled (One-Time).\n", i);
                    }
                }
            }
        } else {
            Serial.println("[Alarm] Failed to read RTC time.");
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS); // 每秒检查一次
    }
}
