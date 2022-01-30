#ifndef Sensors_h
#define Sensors_h

#include "Arduino.h"

class Sensors {
   public:
    Sensors(int moistureSensorPin, int temperatureSensorPin, int lightSensorPin);
    /**
    * Returns the ground moisture value in percentage, from 0 (mid air) to 100 (submerged in water).
    */
    int readMoisture();
    int readLight();
    float readTemperature();

   private:
    int _moistureSensorPin;
    int _temperatureSensorPin;
    int _lightSensorPin;
};

#endif
