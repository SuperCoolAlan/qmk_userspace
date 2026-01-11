#pragma once

// WS2812 RGB LED pin for BLOK
#define WS2812_DI_PIN GP29

// RGB Light configuration - 70 LEDs (35 per half)
#define RGBLIGHT_LED_COUNT 70
#define RGBLIGHT_SPLIT
#define RGBLIGHT_LIMIT_VAL 150

// I2C for OLED on BLOK
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP22
#define I2C1_SCL_PIN GP23
