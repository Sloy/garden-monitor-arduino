#ifndef Sensors_h
#define Sensors_h

#include "SensorData.h"

class Sensors {
   public:
    Sensors(int moistureSensorPin, int temperatureSensorPin, int lightSensorPin);
    SensorData read();
    int readMoisture();
    int readLight();
    float readTemperature();

   private:
    int _moistureSensorPin;
    int _temperatureSensorPin;
    int _lightSensorPin;
};

#endif
