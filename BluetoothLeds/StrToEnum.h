#ifndef _STRTOENUM_H_
#define _STRTOENUM_H_

enum LedMode {
  rgbFlow,
  road,
};


LedMode strToEnum(String str) {
  str.trim();
  if (str == "rgbFlow") {
    return rgbFlow;
  } else if (str == "road") {
    return road;
  } else {
    return road;
  }
}

#endif