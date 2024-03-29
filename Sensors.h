#ifndef Sensors_h
#define Sensors_h

#include "SensorData.h"

class Sensors {
   public:
    Sensors();
    SensorData read();
    int readMoisture();
    int readLight();
    float readTemperature();
    float readBattery();

   private:
    int fakeMoisture();
    int fakeLight();
    float fakeTemperature();
};

#endif
