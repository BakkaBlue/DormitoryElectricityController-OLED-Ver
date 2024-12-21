#include "aht10.h"

#define CUSTOM_SDA_PIN 16 // 自定义 SDA 引脚
#define CUSTOM_SCL_PIN 15 // 自定义 SCL 引脚

// 创建全局的 AHT10 对象
Adafruit_AHTX0 aht;

// 使用自定义 I2C 对象
TwoWire customWire = TwoWire(0); // 使用 Wire0 或其他编号

bool aht10_init(int sdaPin, int sclPin) {
    if (sdaPin != -1 && sclPin != -1) {         // 自定义引脚初始化 I2C
        customWire.begin(sdaPin, sclPin);
        return aht.begin(&customWire);          // 使用自定义的 Wire 对象
    } else {
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

// AHT10 任务
void AHT10_Task(void *parameter) {
    if (!aht10_init(CUSTOM_SDA_PIN, CUSTOM_SCL_PIN)) {
        Serial.println("Failed to initialize AHT10!");
        vTaskDelete(NULL);
    }

    while (true) {
        float temperature, humidity;
        if (aht10_read(temperature, humidity)) {
            Serial.printf("Temperature: %.2f °C, Humidity: %.2f %%\n", temperature, humidity);
        } else {
            Serial.println("Failed to read data from AHT10.");
        }
        vTaskDelay(30000 / portTICK_PERIOD_MS); // 每 30 秒读取一次 AHT10 数据
    }
}
