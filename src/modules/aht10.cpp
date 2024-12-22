#include "aht10.h"

// 创建全局 AHT10 对象
Adafruit_AHTX0 aht;

// 信号量（由 main.cpp 中初始化）
extern SemaphoreHandle_t aht10_signal;

bool aht10_init(int sdaPin, int sclPin) {
    Wire.begin(sdaPin, sclPin);

    if (!aht.begin(&Wire)) {
        Serial.println("[AHT10] Initialization failed.");
        return false;
    }

    Serial.println("[AHT10] Initialization successful.");
    return true;
}

void aht10_task(void *parameter) {
    SemaphoreHandle_t i2c_mutex = (SemaphoreHandle_t)parameter;

    while (true) {
        // 等待 DS3231 的信号量
        if (xSemaphoreTake(aht10_signal, portMAX_DELAY)) {
            if (xSemaphoreTake(i2c_mutex, portMAX_DELAY)) { // 获取 I2C 互斥锁
                float temperature, humidity;
                sensors_event_t humidityEvent, temperatureEvent;

                aht.getEvent(&humidityEvent, &temperatureEvent);
                temperature = temperatureEvent.temperature;
                humidity = humidityEvent.relative_humidity;

                Serial.printf("[AHT10] Temperature: %.2f °C, Humidity: %.2f %%\n", 
                              temperature, humidity);

                xSemaphoreGive(i2c_mutex); // 释放 I2C 互斥锁
            } else {
                Serial.println("[AHT10] Failed to acquire I2C mutex.");
            }
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS); // 避免过多占用资源
    }
}
