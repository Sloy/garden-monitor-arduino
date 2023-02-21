#include "SensorData.h"

SensorData::SensorData(int moistureValue, float temperatureValue, int lightValue, float batteryValue) {
    moisture = moistureValue;
    temperature = temperatureValue;
    light = lightValue;
    batteryVoltage = batteryValue;

}