#ifndef DS3231_H
#define DS3231_H

#include <Arduino.h>
#include "RTClib.h"

void ds3231_init();
void ds3231_task(void *parameter);

#endif // DS3231_H
