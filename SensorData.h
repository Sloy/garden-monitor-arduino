#ifndef SensorData_h
#define SensorData_h

class SensorData {
   public:
    SensorData(int moistureValue, float temperatureValue, int lightValue, float batteryValue);
    int moisture;
    float temperature;
    int light;
    float batteryVoltage;
};

#endif
