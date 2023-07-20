#ifndef _MODE_H_
#define _MODE_H_

class Mode {
  private : 
    String mode;
    int speed;
    int brightness;
    int red;
    int green;
    int blue;

  public :
  Mode(String mode, int speed, int brightness, int red, int green, int blue);

  String getMode() const;
  int getSpeed() const;
  int getBrightness() const;
  int getRed() const;
  int getGreen() const;
  int getBlue() const;
};

Mode::Mode(String mode, int speed, int brightness, int red, int green, int blue) {
  this->mode = mode;
  this->speed = speed;
  this->brightness = brightness;
  this->red = red;
  this->green = green;
  this->blue = blue;
}

String Mode::getMode() const {
  return mode;
}

int Mode::getSpeed() const {
  return speed;
}

int Mode::getBrightness() const {
  return brightness;
}

int Mode::getRed() const {
  return red;
}

int Mode::getGreen() const {
  return green;
}

int Mode::getBlue() const {
  return blue;
}

#endif