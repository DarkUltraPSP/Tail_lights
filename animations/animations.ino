#include <Adafruit_NeoPixel.h>

#define LED_PIN 2
#define NUM_LEDS 144
#define BRIGHTNESS 255

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();  // Initialize all pixels to "off"
  strip.setBrightness(BRIGHTNESS);
}

void loop() {
  rainbowSparkle(5);
}

void unicolorSparkle(int red, int green, int blue, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, red, green, blue);
  }
  addSparkles(random(2));
  strip.show();
  delay(wait);
}

void rainbowSparkle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    addSparkles(random(0, 2));
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

void addSparkles(uint8_t count) {
  for (uint8_t i = 0; i < count; i++) {
    uint8_t pixel = random(strip.numPixels());
    strip.setPixelColor(pixel, strip.Color(255, 255, 255));  // Set pixel to white
  }
}

void whiteChase() {
  static int currentLED = 0;

  // Turn on the current LED
  strip.setPixelColor(currentLED, 255, 255, 255);

  currentLED = (currentLED + 1) % NUM_LEDS;
}

void whiteOppositeChase() {
  static int currentLED1 = 0;
  static int currentLED2 = strip.numPixels() / 2;

  // Turn on the current LED
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

  // Turn on the current LED
  strip.setPixelColor(currentLED1, 255, 255, 255);
  strip.setPixelColor(currentLED1 + 1, 255, 255, 255);

  // Turn on the current LED
  strip.setPixelColor(currentLED2, 255, 255, 255);
  strip.setPixelColor(currentLED2 - 1, 255, 255, 255);


  currentLED1 = (currentLED1 + 1) % NUM_LEDS;
  currentLED2 = (currentLED2 - 1 + NUM_LEDS) % NUM_LEDS;
}

void animation_luminosite() {
  int luminosite_max = 255;  // Valeur maximale de la luminosité
  int pas = 5;  // Pas d'augmentation/diminution de la luminosité

  // Augmentation de la luminosité
  for (int luminosite = 0; luminosite < luminosite_max; luminosite += pas) {
    for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, strip.Color(luminosite, luminosite, luminosite));
    }
    strip.show();
    delay(10);
  }

  // Diminution de la luminosité
  for (int luminosite = luminosite_max; luminosite >= 1; luminosite -= pas) {
    for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, strip.Color(luminosite, luminosite, luminosite));
    }
    strip.show();
    delay(10);
  }
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
