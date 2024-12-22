#include <U8g2lib.h>

// 自定义引脚
#define CUSTOM_SDA_PIN 16
#define CUSTOM_SCL_PIN 15

extern SemaphoreHandle_t i2c_mutex;

// U8g2 OLED 对象
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, CUSTOM_SCL_PIN, CUSTOM_SDA_PIN);

// 初始化 OLED
bool oled_init() {
    u8g2.begin();
    u8g2.clearBuffer(); // 清空显示缓冲区
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 10, "OLED Ready!");
    u8g2.sendBuffer();
    Serial.println("[OLED] Initialized successfully.");
    return true;
}

// OLED 任务
void oled_task(void *parameter) {
    while (true) {
        if (xSemaphoreTake(i2c_mutex, portMAX_DELAY)) { // 获取 I2C 互斥锁
            // 示例：显示动态内容
            u8g2.clearBuffer();
            u8g2.setFont(u8g2_font_ncenB08_tr);
            u8g2.drawStr(0, 10, "Dynamic Content");
            u8g2.drawStr(0, 30, "Time: 12:34");
            u8g2.sendBuffer();

            xSemaphoreGive(i2c_mutex); // 释放 I2C 互斥锁
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS); // 每秒刷新一次
    }
}
