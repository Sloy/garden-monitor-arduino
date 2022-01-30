
#include "Sensors.h"

#include "Arduino.h"

Sensors::Sensors(int moistureSensorPin, int temperatureSensorPin, int lightSensorPin) {
    _moistureSensorPin = moistureSensorPin;
    _temperatureSensorPin = temperatureSensorPin;
    _lightSensorPin = lightSensorPin;
}

int Sensors::readMoisture() {
    delay(5);
    int moistureValue = analogRead(_moistureSensorPin);
    int percentage = 100 - map(moistureValue, 250, 1023, 0, 100);
    return percentage;
}
int Sensors::readLight() {
    delay(5);
    int lightValue = analogRead(_lightSensorPin);
    int percentage = map(lightValue, 0, 1023, 0, 100);
    return percentage;
}
float Sensors::readTemperature() {
    delay(5);
    int tempValue = analogRead(_temperatureSensorPin);
    float voltage = (tempValue / 1024.0) * 5.0;
    float temperature = (voltage - .5) * 100;
    return temperature;
}