
//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"
#include "Animations.h"
#include "Mode.h"
#include "Tools.h"

int breakPin = 14;
int lightsPin = 26;
int blinkerPin = 33;

Mode mode = Mode("road", 0, 100, 255, 0, 0);

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void handleInterrupt() {
  if (digitalRead(breakPin) == LOW) {
    mode = Mode("road", 0, 100, 255, 0, 0);
  }
  Serial.println("Interrupt");
}

void setup() {
  //Bluetooth Setup
  Serial.begin(115200);
  SerialBT.begin("TailLights"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  //Led Setup
  strip.begin();
  strip.show();

  //button setup
  pinMode(breakPin, INPUT);
  pinMode(lightsPin, INPUT);
  pinMode(blinkerPin, INPUT);
  
    // attachInterrupt(digitalPinToInterrupt(breakPin), handleInterrupt, CHANGE);
  
}

void loop() {
  if (SerialBT.available()) {
    Serial.println("Serial available");
    String json = SerialBT.readString();
    mode = deserializeMode(json);
    Serial.println(mode.getMode());
  }

  if (mode.getMode() == "rgbflow" || mode.getMode() == "rgbflow chase" || mode.getMode() == "rgbflow sparkles") {
    rainbow(mode.getMode(), mode.getSpeed(), mode.getBrightness());
  }

  if (mode.getMode() == "static" || mode.getMode() == "static chase" || mode.getMode() == "static sparkles") {
    staticColor(mode.getMode(), mode.getRed(), mode.getGreen(), mode.getBlue(), mode.getBrightness());
  }

  if (mode.getMode() == "breathing") {
    breathing(mode.getSpeed(), mode.getBrightness(), mode.getRed(), mode.getGreen(), mode.getBlue());
  }

  if (mode.getMode() == "shutdown") {
    for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, 0, 0, 0);
      strip.show();
    }
  }

  if (mode.getMode() == "road") {
    roadLights(lightsPin, breakPin, blinkerPin);
  }
}