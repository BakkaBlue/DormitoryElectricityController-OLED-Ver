#include "aht10.h"

#define CUSTOM_SDA_PIN 16 // 自定义 SDA 引脚
#define CUSTOM_SCL_PIN 15 // 自定义 SCL 引脚

SemaphoreHandle_t aht10_signal;

// 创建全局的 AHT10 对象
Adafruit_AHTX0 aht;

// 使用自定义 I2C 对象
TwoWire customWire = TwoWire(0); // 使用 Wire0 或其他编号

bool aht10_init(int sdaPin, int sclPin) {
    if (aht10_signal == NULL) {
        Serial.println("[AHT10] Failed to create semaphore.");
    }
    if (sdaPin != -1 && sclPin != -1) {         // 自定义引脚初始化 I2C
        if (!customWire.begin(sdaPin, sclPin)) {
            Serial.println("Failed to initialize I2C for AHT10");
            return false;
        }
        if (!aht.begin(&customWire)) {
            return false;
        }
        return true; // 初始化成功
    } else {
        Serial.println("Invalid I2C pins for AHT10 initialization");
        return false;
    }
}

bool aht10_read(float &temperature, float &humidity) {
    sensors_event_t humidityEvent, temperatureEvent;
    aht.getEvent(&humidityEvent, &temperatureEvent); // 获取数据

    if (humidityEvent.relative_humidity >= 0 && temperatureEvent.temperature >= -40) {
        temperature = temperatureEvent.temperature;
        humidity = humidityEvent.relative_humidity;
        return true; // 数据有效
    } else {
        Serial.println("Invalid data read from AHT10");
        return false; // 数据无效
    }
}

// AHT10 任务
void aht10_task(void *parameter) {
    SemaphoreHandle_t i2c_mutex = (SemaphoreHandle_t)parameter;

    while (true) {
        // 等待 DS3231 任务的信号量
        if (xSemaphoreTake(aht10_signal, portMAX_DELAY)) {
            if (xSemaphoreTake(i2c_mutex, portMAX_DELAY)) { // 获取 I2C 互斥锁
                aht10_init(CUSTOM_SDA_PIN, CUSTOM_SCL_PIN); // 初始化 AHT10
                float temperature, humidity;
                if (aht10_read(temperature, humidity)) {
                    Serial.printf("[AHT10] Temperature: %.2f °C, Humidity: %.2f %%\n", temperature, humidity);
                } else {
                    Serial.println("[AHT10] Failed to read data.");
                }
                xSemaphoreGive(i2c_mutex); // 释放 I2C 互斥锁
            } else {
                Serial.println("[AHT10] Failed to acquire I2C mutex.");
            }
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS); // 避免任务占用过多资源
    }
}

