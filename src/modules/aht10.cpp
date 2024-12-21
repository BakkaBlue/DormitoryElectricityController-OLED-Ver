#include "aht10.h"

// 创建全局的 AHT10 对象
Adafruit_AHTX0 aht;

// 使用自定义 I2C 对象
TwoWire customWire = TwoWire(0); // 使用 Wire0 或其他编号

bool aht10_init(int sdaPin, int sclPin) {
    if (sdaPin != -1 && sclPin != -1) {
        // 自定义引脚初始化 I2C
        customWire.begin(sdaPin, sclPin);
        return aht.begin(&customWire); // 使用自定义的 Wire 对象
    } else {
        // 默认引脚初始化 I2C
        return aht.begin();
    }
}

bool aht10_read(float &temperature, float &humidity) {
    sensors_event_t humidityEvent, temperatureEvent;
    aht.getEvent(&humidityEvent, &temperatureEvent); // 获取数据

    if (humidityEvent.relative_humidity >= 0 && temperatureEvent.temperature >= -40) {
        temperature = temperatureEvent.temperature;
        humidity = humidityEvent.relative_humidity;
        return true; // 数据有效
    }
    return false; // 数据无效
}