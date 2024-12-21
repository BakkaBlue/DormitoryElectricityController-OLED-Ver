/*
void drawThickLine(int x1, int y1, int x2, int y2, int thickness) {
  for (int i = 0; i < thickness; i++) {
    display.drawLine(x1 + i, y1, x2 + i, y2, RED);  // 绘制每一条平行的线
  }
}
*/
#include <Arduino.h>
#include "aht10.h"
#include "Wire.h"
#include "ds3231.h" // 引入 DS3231 的头文件

#define CUSTOM_SDA_PIN 16 // 自定义 SDA 引脚
#define CUSTOM_SCL_PIN 15 // 自定义 SCL 引脚

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

void setup() {
    Serial.begin(115200);

    // 初始化 I2C
    Wire.begin(CUSTOM_SDA_PIN, CUSTOM_SCL_PIN);

    // 初始化 DS3231
    ds3231_init();

    // 创建 DS3231 任务（优先级更低）
    xTaskCreate(ds3231_task, "DS3231 Task", 4096, NULL, 1, NULL);

    // 创建 AHT10 任务（优先级较高）
    xTaskCreate(AHT10_Task, "AHT10 Task", 4096, NULL, 2, NULL);
}

void loop() {
    // 主循环为空，由任务处理
}



/*
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>

// 屏幕引脚定义
#define SCREEN_CS    38   // 片选引脚
#define SCREEN_DC    39  // 数据/命令选择引脚
#define SCREEN_RST   40  // 重置引脚
#define SCREEN_MOSI  41  // MOSI引脚
#define SCREEN_SCK   42  // SCK引脚

// 屏幕宽度和高度
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

// Color definitions
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF
*/

/*
#include <Wire.h>
#include <Adafruit_AHTX0.h>

// 定义自定义I2C引脚
#define SDA_PIN 16  // 自定义SDA引脚
#define SCL_PIN 15  // 自定义SCL引脚

Adafruit_AHTX0 aht;

void setup() {
  Serial.begin(115200);
  Serial.println("Adafruit AHT10/AHT20 demo!");

  // 初始化I2C总线，使用自定义的SDA和SCL引脚
  Wire.begin(SDA_PIN, SCL_PIN);
  
  if (!aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 or AHT20 found");
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);  // 获取最新的温湿度数据

  // 输出温湿度数据到串口监视器
  Serial.print("Temperature: "); 
  Serial.print(temp.temperature); 
  Serial.println(" °C");

  Serial.print("Humidity: "); 
  Serial.print(humidity.relative_humidity); 
  Serial.println("%");

  delay(1000);  // 每500ms更新一次数据
}

*/