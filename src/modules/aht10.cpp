#include "aht10.h"

// 创建 AHT10 传感器对象
static Adafruit_AHTX0 aht;

// 初始化 AHT10 传感器
bool aht10_initial(void) {
    if (!aht.begin()) {
        Serial.println("AHT10 初始化失败，请检查连接!");
        return false;
    }
    Serial.println("AHT10 初始化成功");
    return true;
}

// 读取温湿度数据
bool aht10_number_read(float *temperature, float *humidity) {
    sensors_event_t humidity_event, temp_event;

    if (!aht.getEvent(&humidity_event, &temp_event)) {
        Serial.println("读取 AHT10 数据失败!");
        return false;
    }

    *temperature = temp_event.temperature;
    *humidity = humidity_event.relative_humidity;

    return true;
}
