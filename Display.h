#ifndef Display_h
#define Display_h

#include <LiquidCrystal.h>

#include "Arduino.h"

class Display {
   public:
    Display(bool enabled);
    void showSensors(int moisture, float temperature, int light);

   private:
    bool _enabled;
};

#endif
