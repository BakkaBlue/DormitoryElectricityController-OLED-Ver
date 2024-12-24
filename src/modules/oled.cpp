#include <U8g2lib.h>
#include "oled.h"

// U8g2 OLED 对象
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// 引用全局互斥锁
extern SemaphoreHandle_t i2c_mutex;

// 引用全局时间、日期和温湿度变量
extern char current_time[16];
extern char current_date[16];
extern char current_temp_hum[32];

bool oled_init(int sdaPin, int sclPin) {
    Wire.begin(sdaPin, sclPin);
    Wire.setClock(100000); // 设置 I2C 频率为 100kHz
    u8g2.begin();
    u8g2.clearBuffer(); // 清空显示缓冲区
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 10, "OLED Ready!");
    u8g2.sendBuffer();
    Serial.println("[OLED] Initializion successful.");
    return true;
}

void oled_task(void *parameter) {
    while (true) {
        if (xSemaphoreTake(i2c_mutex, portMAX_DELAY)) { // 获取 I2C 互斥锁
            u8g2.clearBuffer();
            u8g2.setFont(u8g2_font_ncenB08_tr);

            // 显示日期
            u8g2.drawStr(0, 10, "Date:");
            u8g2.drawStr(40, 10, current_date);

            // 显示时间
            u8g2.drawStr(0, 30, "Time:");
            u8g2.drawStr(40, 30, current_time);

            // 显示温湿度
            u8g2.drawStr(0, 50, current_temp_hum);

            u8g2.sendBuffer();
            xSemaphoreGive(i2c_mutex); // 释放 I2C 互斥锁
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS); // 每秒刷新一次
    }
}
