#ifndef Display_h
#define Display_h

#include "SensorData.h"

class Display {
   public:
    void begin();
    void show(SensorData sensorData);
    void showSensors(int moisture, float temperature, int light);
};

#endif
