#include "rgb_led.h"
#include <Arduino.h>

Adafruit_NeoPixel pixels(RGB_LED_NUM, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);

// Определение цветов
uint32_t COLOR_RED = pixels.Color(255, 0, 0);
uint32_t COLOR_GREEN = pixels.Color(0, 255, 0);
uint32_t COLOR_BLUE = pixels.Color(0, 0, 255);
uint32_t COLOR_YELLOW = pixels.Color(255, 255, 0);
uint32_t COLOR_CYAN = pixels.Color(0, 255, 255);
uint32_t COLOR_PURPLE = pixels.Color(255, 0, 255);
uint32_t COLOR_WHITE = pixels.Color(255, 255, 255);
uint32_t COLOR_BLACK = pixels.Color(0, 0, 0);

// Переменные для управления миганием
static uint32_t currentColor = COLOR_BLACK;
static unsigned long blinkStartTime = 0;
static unsigned long blinkDuration = 0;
static bool isBlinking = false;

void initRGBLED() {
    pixels.begin();
    pixels.setBrightness(RGB_LED_BRIGHTNESS);
    pixels.clear();
    pixels.show();
    Serial.printf("RGB LED initialized on pin %d\n", RGB_LED_PIN);
}

void setLEDColor(uint8_t r, uint8_t g, uint8_t b) {
    pixels.setPixelColor(0, r, g, b);
    pixels.show();
}

void setLEDColor(uint32_t color) {
    pixels.setPixelColor(0, color);
    pixels.show();
}

void setLEDBrightness(uint8_t brightness) {
    pixels.setBrightness(brightness);
    pixels.show();
}

void setStatusColor(uint32_t color) {
    currentColor = color;
    if (!isBlinking) {
        setLEDColor(color);
    }
}

void blinkLED(uint32_t color, unsigned long duration) {
    blinkStartTime = millis();
    blinkDuration = duration;
    isBlinking = true;
    setLEDColor(color);
}

void updateLEDStatus() {
    if (isBlinking) {
        if (millis() - blinkStartTime >= blinkDuration) {
            isBlinking = false;
            setLEDColor(currentColor);
        }
    }
}