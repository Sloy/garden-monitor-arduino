#ifndef SensorData_h
#define SensorData_h

class SensorData {
   public:
    SensorData(int moistureValue, float temperatureValue, int lightValue);
    int moisture;
    float temperature;
    int light;
};

#endif
