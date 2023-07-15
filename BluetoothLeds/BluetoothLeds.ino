
//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"
#include "StrToEnum.h"
#include "animations.h"

LedMode ledMode = rgbFlow;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  //Bluetooth Setup
  Serial.begin(115200);
  SerialBT.begin("TailLights"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  //Led Setup
  strip.begin();
  strip.show();
}

void loop() {

  if (SerialBT.available()) {
    ledMode = strToEnum(SerialBT.readString());
  }

  switch (ledMode)
  {
    case rgbFlow:
      rainbow(5);
      break;
    
    default:
      shutdown();
      break;
  }
}

void shutdown() {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);
  }
  strip.show();
}