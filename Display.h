#ifndef Display_h
#define Display_h

#include <LiquidCrystal.h>

#include "SensorData.h"

class Display {
   public:
    Display(bool enabled);
    void show(SensorData sensorData);
    void showSensors(int moisture, float temperature, int light);

   private:
    bool _enabled;
};

#endif
