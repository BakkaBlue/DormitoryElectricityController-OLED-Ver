/*
#pragma once
#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Arduino.h>
#include <Adafruit_SSD1351.h> 

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

// 声明全局变量

// 声明函数
void display_init();
void display_clear();
void display_text(const char *text, int x, int y, int size, uint16_t color);
void display_draw_rect(int x, int y, int w, int h, uint16_t color);
void display_fill_rect(int x, int y, int w, int h, uint16_t color);
void display_draw_pixel(int x, int y, uint16_t color);
void display_set_window(int x, int y, int w, int h);
void display_draw_line(int x0, int y0, int x1, int y1, uint16_t color);

#endif // DISPLAY_H
 */


#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_SSD1351.h>
extern Adafruit_SSD1351 display;

void display_init();

#endif // DISPLAY_H
