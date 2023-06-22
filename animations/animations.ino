#include <Adafruit_NeoPixel.h>

#define LED_PIN 2
#define NUM_LEDS 144
#define BRIGHTNESS 10

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();  // Initialize all pixels to "off"
  strip.setBrightness(BRIGHTNESS);
}

void loop() {
  rainbowChase(5);
}

void rainbowSparkle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    addSparkles(random(0,2));
    strip.show();
    delay(wait);
  }
}

void rainbowChase(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    whiteChase();
    strip.show();
    delay(wait);
  }
}

void blinkers() {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 255, 80, 0);
  }
  strip.show();
}

void addSparkles(uint8_t count) {
  for (uint8_t i = 0; i < count; i++) {
    uint8_t pixel = random(strip.numPixels());
    strip.setPixelColor(pixel, strip.Color(255, 255, 255));  // Set pixel to white
  }
}

void whiteChase() {
  static int currentLED = 0;
  static int previousLED = NUM_LEDS - 1;

  // Turn on the current LED
  strip.setPixelColor(currentLED, 255, 255, 255);
  strip.show();

  // Update the LED index values
  previousLED = currentLED;
  currentLED = (currentLED + 1) % NUM_LEDS;
}

// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r.
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
