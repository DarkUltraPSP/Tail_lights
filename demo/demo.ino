#include <FastLED.h>

#define NUM_LEDS 144
#define LED_PIN 2

const int stop = 14;
const int blinkers = 33;
const int lights = 34;

int lightstate = 0;
int stopState = 0;
int blinkerState = 0;


CRGB leds[NUM_LEDS];

void setup() {
  pinMode(stop, INPUT);
  pinMode(blinkers, INPUT);
  pinMode(lights, INPUT);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
}

void loop() {
  lightstate = digitalRead(lights);
  stopState = digitalRead(stop);
  blinkerState = digitalRead(blinkers);


  if (stopState == LOW) {
    FastLED.setBrightness(255);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(255, 0, 0);
    }
  } else if (blinkerState == LOW) {
    FastLED.setBrightness(255);
    for (int i = 0; i < 40; i++) {
      leds[i] = CRGB::Orange;
      FastLED.delay(10);
    }

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
    }

  } else if (lightstate == LOW) {
    FastLED.setBrightness(60);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(255, 0, 0);
    }
  }
  else {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
    }
  }

  FastLED.show();
  delay(100);
}