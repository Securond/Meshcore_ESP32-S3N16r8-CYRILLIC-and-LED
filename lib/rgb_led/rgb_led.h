#pragma once
#include <Adafruit_NeoPixel.h>

#ifndef RGB_LED_PIN
    #error "RGB_LED_PIN must be defined in platformio.ini"
#endif

#ifndef RGB_LED_NUM
    #define RGB_LED_NUM 1
#endif

#ifndef RGB_LED_BRIGHTNESS
    #define RGB_LED_BRIGHTNESS 50
#endif

extern Adafruit_NeoPixel pixels;

// Предопределенные цвета (для использования в коде)
extern uint32_t COLOR_RED;
extern uint32_t COLOR_GREEN;
extern uint32_t COLOR_BLUE;
extern uint32_t COLOR_YELLOW;
extern uint32_t COLOR_CYAN;
extern uint32_t COLOR_PURPLE;
extern uint32_t COLOR_WHITE;
extern uint32_t COLOR_BLACK;

void initRGBLED();
void setLEDColor(uint8_t r, uint8_t g, uint8_t b);
void setLEDColor(uint32_t color);
void setLEDBrightness(uint8_t brightness);
void setStatusColor(uint32_t color);
void blinkLED(uint32_t color, unsigned long duration);
void updateLEDStatus();