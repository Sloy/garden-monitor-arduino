
#include "Sensors.h"

#include "Arduino.h"
#include "SensorData.h"
#include "config.h"

Sensors::Sensors() {
    pinMode(MOISTURE_POWER, OUTPUT);
    digitalWrite(MOISTURE_POWER, HIGH);
}

SensorData Sensors::read() {
    return SensorData(readMoisture(), readTemperature(), readLight());
}

int Sensors::readMoisture() {
    digitalWrite(MOISTURE_POWER, HIGH);
    int moistureValue = analogRead(MOISTURE_PIN);
    delay(10);
    digitalWrite(MOISTURE_POWER, LOW);
    int percentage = 100 - map(moistureValue, 250, 1023, 0, 100);
    return percentage;
}
int Sensors::readLight() {
    int lightValue = analogRead(LIGHT_PIN);
    delay(10);
    int percentage = map(lightValue, 0, 1023, 0, 100);
    return percentage;
}
float Sensors::readTemperature() {
    int tempValue = analogRead(TEMPERATURE_PIN);
    delay(10);
    float voltage = (tempValue / 1024.0) * 5.0;
    float temperature = (voltage - .5) * 100;
    return temperature;
}