#ifndef _JSONDESERIALIZE_H_
#define _JSONDESERIALIZE_H_
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include "Mode.h"

Mode deserializeMode(String json) {
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, json);
  String mode = doc["mode"];
  int speed = doc["speed"];
  int brightness = doc["brightness"];
  int red = doc["red"];
  int green = doc["green"];
  int blue = doc["blue"];
  return Mode(mode, speed, brightness, red, green, blue);
}

#endif