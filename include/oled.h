#ifndef OLED_H
#define OLED_H

#include <Wire.h>
#include <U8g2lib.h>

bool oled_init(int sdaPin, int sclPin);
void oled_task(void *parameter);

#endif // OLED_H