/*
#include <Arduino.h>
#include <stdio.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <Adafruit_AHTX0.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <SPI.h>

#define SerialDebugging true

const char* ssid = "Cyan";
const char* password = "bakkablue";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"pool.ntp.org", 0, 3600 * 8);
//                           HH:MM:SS
// timeClient initializes to 10:00:00 if it does not receive an NTP packet
// before the 100ms timeout.
// without isTimeSet() the LED would be switched on, although the time
// was not yet set correctly.

// Screen dimensions
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 128 // Change this to 96 for 1.27" OLED.

// You can use any (4 or) 5 pins 
const uint8_t   OLED_pin_scl_sck        = 42;
const uint8_t   OLED_pin_sda_mosi       = 41;
const uint8_t   OLED_pin_res_rst        = 40;
const uint8_t   OLED_pin_dc_rs          = 39;
const uint8_t   OLED_pin_cs_ss          = 38;

const uint8_t   I2C_scl             = 15;
const uint8_t   I2C_sda             = 16;

Adafruit_SSD1351 display(128, 128, OLED_pin_scl_sck, OLED_pin_sda_mosi, OLED_pin_res_rst, OLED_pin_dc_rs, OLED_pin_cs_ss); 
Adafruit_AHTX0 aht10;

// Color definitions
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

// declare the display
Adafruit_SSD1351 oled =
    Adafruit_SSD1351(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        &SPI,
        OLED_pin_cs_ss,
        OLED_pin_dc_rs,
        OLED_pin_res_rst
    );

void drawThickLine(int x1, int y1, int x2, int y2, int thickness) {
  for (int i = 0; i < thickness; i++) {
    display.drawLine(x1 + i, y1, x2 + i, y2, RED);  // 绘制每一条平行的线
  }
}

void task1(void *pt) {
  pinMode(21, OUTPUT);
  while (1) {
    digitalWrite(21, !digitalRead(21));
    vTaskDelay(3000);
  }
}

void uiTask(void* parameter) {
  // 等待 WiFi 连接完成
    while (1) {
      // 清屏
      display.fillScreen(BLACK);

      display.drawRect(0, 0, 128, 128, CYAN);  // 绘制外框
      // 绘制粗线
      drawThickLine(0, 64, 128, 64, 3);  // 参数 (起点x, 起点y, 终点x, 终点y, 粗细)

      // 显示当前时间
      display.setTextColor(WHITE);  // 设置绘制颜色为白色
      display.setTextSize(3);  // 字体大小
      display.setCursor(40, 30);
      display.print(timeClient.getFormattedTime());  // 显示当前时间

      // BLE 和 ToDo list 部分
      display.setCursor(10, 90);
      display.print("BLE");

      // 绘制 ToDo list 方框
      display.drawRect(40, 80, 60, 20, WHITE);  // 绘制方框

      // 刷新屏幕
      vTaskDelay(5000 / portTICK_PERIOD_MS);  // 每隔5秒刷新一次屏幕
    }
}


void setup() {

    #if (SerialDebugging)
    Serial.begin(115200);
    while (!Serial);
    Serial.println();
    #endif

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay (500);
        Serial.print (".");
    }

    if (xTaskCreate(task1,
                  "Blink 23",
                  1024,
                  NULL,
                  1,
                  NULL) == pdPASS)
    Serial.println("Task1 Created.");

    display.begin();  // 初始化显示屏
    display.fillScreen(BLACK);    // 清屏

    timeClient.begin();
}

void loop() {

}

*/

/*
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "aht10.h"
#include "ds3231.h"
#include "display.h"
#include "buzzer.h"
#include "button.h"

// 全局变量
float temperature, humidity;
bool alarmTriggered = false;
DateTime now;

// 任务函数声明
void displayTask(void *pvParameters);
void sensorTask(void *pvParameters);
void buttonTask(void *pvParameters);
void alarmTask(void *pvParameters);

int main(void) {
    // 初始化硬件模块
    aht10_init();
    ds3231_init();
    display_init();
    buzzer_init();
    button_init();

    // 创建任务
    xTaskCreate(displayTask, "Display Task", 2048, NULL, 1, NULL);
    xTaskCreate(sensorTask, "Sensor Task", 2048, NULL, 2, NULL);
    xTaskCreate(buttonTask, "Button Task", 2048, NULL, 3, NULL);
    xTaskCreate(alarmTask, "Alarm Task", 2048, NULL, 2, NULL);

    // 启动调度器
    vTaskStartScheduler();

    // 永远不会到达这里
    while (1);
    return 0;
}


*/
#include <Arduino.h>
#include "modules/oled_display.cpp"

void setup() {
    display_init();
}

void loop() {
}
