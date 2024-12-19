#include "oled_display.h"
#include <Adafruit_SSD1351.h>  // 引入Adafruit_SSD1351库
#include <SPI.h>

// 定义全局变量（只有在此处定义一次）
Adafruit_SSD1351 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, SCREEN_CS, SCREEN_DC, SCREEN_RST);

// 初始化 OLED 屏幕
void display_init() {
    // 初始化屏幕并设置 SPI 通信频率
    display.begin(8000000);  // SPI 时钟频率设置为 8MHz
    Serial.println("SSD1351 初始化完成!");
    display.fillScreen(BLACK);  // 清空屏幕
}

// 清空屏幕
void display_clear() {
    display.fillScreen(BLACK);  // 填充黑色清空屏幕
}

// 显示文本
void display_text(const char *text, int x, int y, int size, uint16_t color) {
    display.setTextSize(size);       // 设置文本大小
    display.setTextColor(color);     // 设置文本颜色
    display.setCursor(x, y);         // 设置文本起始位置
    display.print(text);             // 打印文本到屏幕
}

// 绘制矩形
void display_draw_rect(int x, int y, int w, int h, uint16_t color) {
    display.drawRect(x, y, w, h, color);  // 绘制一个矩形
}

// 绘制填充矩形
void display_fill_rect(int x, int y, int w, int h, uint16_t color) {
    display.fillRect(x, y, w, h, color);  // 绘制一个填充的矩形
}

// 绘制单个像素
void display_draw_pixel(int x, int y, uint16_t color) {
    display.drawPixel(x, y, color);  // 绘制一个像素点
}

// 设置显示窗口（优化部分刷新）
void display_set_window(int x, int y, int w, int h) {
    display.setAddrWindow(x, y, x + w - 1, y + h - 1);  // 设置刷新区域
}

// 绘制线条
void display_draw_line(int x0, int y0, int x1, int y1, uint16_t color) {
    display.drawLine(x0, y0, x1, y1, color);  // 绘制一条直线
}

// 更新屏幕（无操作，因为 SSD1351 直接写入屏幕）
void display_update() {
    // Adafruit_SSD1351 的绘图方法是即时生效的，无需调用刷新函数
}