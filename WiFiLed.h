#ifndef WiFiLed_h
#define WiFiLed_h

#include <Arduino.h>
class WiFiLed {
   public:
    WiFiLed(float brightness);
    void set(uint8_t red, uint8_t green, uint8_t blue);
    void setRed();
    void setGreen();
    void setBlue();
    void setPurple();

   private:
    float _brightness;
};

#endif
