#include <Arduino.h>
#include <stdio.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
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
const uint8_t   OLED_pin_scl_sck        = 39;
const uint8_t   OLED_pin_sda_mosi       = 38;
const uint8_t   OLED_pin_res_rst        = 37;
const uint8_t   OLED_pin_dc_rs          = 36;
const uint8_t   OLED_pin_cs_ss          = 35;

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

    timeClient.begin();
}

void loop() {

}
