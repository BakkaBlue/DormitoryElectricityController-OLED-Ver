#include "ui.h"
#include "oled.h"

// 菜单项定义
struct MenuItem {
    const uint8_t *icon; // 图标
    const char *text;    // 菜单文字
};

MenuItem menu_items[] = {
    {icon_clock, "Clock"},
    {icon_light, "Power"},
    {icon_settings, "Settings"}
};

const int menu_count = sizeof(menu_items) / sizeof(MenuItem);
int selected_index = 0;

void ui_init() {
    draw_menu();
}

void scroll_menu(int direction) {
    selected_index = (selected_index + direction + menu_count) % menu_count;
    draw_menu();
}

void draw_menu() {
    u8g2.clearBuffer();

    // 上一个菜单项
    int prev_index = (selected_index - 1 + menu_count) % menu_count;
    u8g2.drawBitmap(4, 0, 16, 16, menu_items[prev_index].icon);
    u8g2.drawStr(24, 8, menu_items[prev_index].text);

    // 当前选中菜单项
    u8g2.drawBox(0, 20, 128, 16); // 高亮框
    u8g2.setDrawColor(0); // 反色文字
    u8g2.drawBitmap(4, 20, 16, 16, menu_items[selected_index].icon);
    u8g2.drawStr(24, 28, menu_items[selected_index].text);
    u8g2.setDrawColor(1); // 恢复颜色

    // 下一个菜单项
    int next_index = (selected_index + 1) % menu_count;
    u8g2.drawBitmap(4, 40, 16, 16, menu_items[next_index].icon);
    u8g2.drawStr(24, 48, menu_items[next_index].text);

    u8g2.sendBuffer();
}

void handle_input(int input) {
    if (input == INPUT_UP) {
        scroll_menu(-1);
    } else if (input == INPUT_DOWN) {
        scroll_menu(1);
    } else if (input == INPUT_SELECT) {
        Serial.printf("Selected menu: %s\n", menu_items[selected_index].text);
    }
}
