#ifndef ALARM_BUZZER_H
#define ALARM_BUZZER_H

#include <Arduino.h>

// 最大支持的闹钟数量
#define MAX_ALARMS 5

// 闹钟类型
enum AlarmType {
    REPEATING, // 每天重复触发
    ONE_TIME   // 一次性闹钟
};

// 闹钟数据结构
struct Alarm {
    int hour;       // 小时
    int minute;     // 分钟
    bool enabled;   // 闹钟是否启用
    AlarmType type; // 闹钟类型
};

// 初始化闹钟模块
void alarm_buzzer_init(int buzzerPin);

// 设置闹钟
bool set_alarm(int index, int hour, int minute, bool enabled, AlarmType type);

// 删除闹钟
bool delete_alarm(int index);

// 显示所有闹钟状态（串口输出）
void list_alarms();

// 任务函数
void alarm_buzzer_task(void *parameter);

#endif // ALARM_BUZZER_H
