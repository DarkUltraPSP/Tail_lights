#ifndef _ANIMATIONS_H_
#define _ANIMATIONS_H_
#include <Adafruit_NeoPixel.h>

#define LED_PIN 2
#define NUM_LEDS 45
#define BRIGHTNESS 5

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void addSparkles(uint8_t count) {
  for (uint8_t i = 0; i < count; i++) {
    uint8_t pixel = random(strip.numPixels());
    strip.setPixelColor(pixel, strip.Color(255, 255, 255)); 
  }
}

void whiteChase() {
  static int currentLED = 0;

  strip.setPixelColor(currentLED, 255, 255, 255);

  currentLED = (currentLED + 1) % NUM_LEDS;
}

void whiteOppositeChase() {
  static int currentLED1 = 0;
  static int currentLED2 = strip.numPixels() / 2;

  strip.setPixelColor(currentLED1, 255, 255, 255);
  strip.setPixelColor(currentLED1 + 1, 255, 255, 255);

  strip.setPixelColor(currentLED2, 255, 255, 255);
  strip.setPixelColor(currentLED2 + 1, 255, 255, 255);

  currentLED1 = (currentLED1 + 1) % NUM_LEDS;
  currentLED2 = (currentLED2 + 1) % NUM_LEDS;
}

void whiteReverseChase() {
  static int currentLED1 = 0;
  static int currentLED2 = NUM_LEDS - 1;

  strip.setPixelColor(currentLED1, 255, 255, 255);
  strip.setPixelColor(currentLED1 + 1, 255, 255, 255);

  strip.setPixelColor(currentLED2, 255, 255, 255);
  strip.setPixelColor(currentLED2 - 1, 255, 255, 255);

  currentLED1 = (currentLED1 + 1) % NUM_LEDS;
  currentLED2 = (currentLED2 - 1 + NUM_LEDS) % NUM_LEDS;
}

void doubleRainbowChase(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    whiteOppositeChase();
    strip.show();
    delay(wait);
  }
}

void staticColor(String mode, uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness) {
  strip.setBrightness(brightness);

  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, red, green, blue);
  }
  if (mode == "static chase") {
    whiteChase();
  } else if (mode == "static sparkles") {
    addSparkles(random(0, 3));
  }
  strip.show();
}

void rainbow(String mode, uint8_t speed, uint8_t brightness) {
  uint16_t i, j;
  strip.setBrightness(brightness);

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    if (mode == "rgbflow chase") {
      whiteChase();
    } else if (mode == "rgbflow sparkles") {
      addSparkles(random(0, 3));
    }
    strip.show();
    delay(speed);
  }
}

void breathing(uint8_t speed, uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue) {

  for (int i = 0; i < brightness; i++) {
    strip.setBrightness(i);
    strip.setPixelColor(0, red, green, blue);
    strip.show();
    delay(speed);
  }
  for (int i = brightness; i > 0; i--) {
    strip.setBrightness(i);
    strip.setPixelColor(0, red, green, blue);
    strip.show();
    delay(speed);
  }
  strip.show();
}

void roadLights(u_int8_t lightsPin, u_int8_t breakPin, u_int8_t blinkersPin) {
  if (digitalRead(lightsPin) == LOW) {
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, 255, 0, 0);
    }
    strip.setBrightness(100);

  } else if (digitalRead(lightsPin) == HIGH) {
    strip.setBrightness(0);

  } else if (digitalRead(breakPin) == LOW) {
    Serial.println("Break");
    strip.setBrightness(255);
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, 255, 0, 0);
    }
  }

  strip.show();
}

void shutdown() {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);
  }
  strip.show();
}

#endif