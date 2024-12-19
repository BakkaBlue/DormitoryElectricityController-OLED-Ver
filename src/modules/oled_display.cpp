#include "oled_display.h"

Adafruit_SSD1351 display(128, 128, &SPI, 5, 17, 16);

void display_init() {
    display.begin(8000000);
}
