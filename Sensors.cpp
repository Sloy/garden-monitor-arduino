
#include "Sensors.h"

#include "Arduino.h"
#include "SensorData.h"
#include "config.h"

Sensors::Sensors() {
    pinMode(MOISTURE_POWER, OUTPUT);
    digitalWrite(MOISTURE_POWER, LOW);
}

SensorData Sensors::read() {
    SensorData data = SensorData(readMoisture(), readTemperature(), readLight(), readBattery());
    LOG("Sensor data: ");
    LOG("Moisture=");
    LOG(data.moisture);
    LOG("\tTemperature=");
    LOG(data.temperature);
    LOG("\tLight=");
    LOGLN(data.light);
    LOG("\tBattery=");
    LOGLN(data.batteryVoltage);
    return data;
}

int Sensors::readMoisture() {
    if (FAKE_SENSOR) {
        return fakeMoisture();
    }
    digitalWrite(MOISTURE_POWER, HIGH);
    delay(100);
    int moistureValue = analogRead(MOISTURE_PIN);
    delay(10);
    digitalWrite(MOISTURE_POWER, LOW);
    int percentage = 100 - map(moistureValue, 250, 1023, 0, 100);
    return percentage;
}
int Sensors::readLight() {
    if (FAKE_SENSOR) {
        return fakeLight();
    }
    int lightValue = analogRead(LIGHT_PIN);
    delay(10);
    int percentage = map(lightValue, 0, 1023, 0, 100);
    return percentage;
}
float Sensors::readTemperature() {
    if (FAKE_SENSOR) {
        return fakeTemperature();
    }
    int tempValue = analogRead(TEMPERATURE_PIN);
    delay(10);
    float voltage = (tempValue / 1024.0) * BOARD_VOLTAGE;
    float temperature = (voltage - .5) * 100;
    return temperature;
}
float Sensors::readBattery() {
    int sensorValue = analogRead(ADC_BATTERY);
    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 4.3V):
    return sensorValue * (BOARD_VOLTAGE / 1023.0);
}

int Sensors::fakeMoisture() {
    return random(45, 60);
}

int Sensors::fakeLight() {
    return random(60, 75);
}

float Sensors::fakeTemperature() {
    return ((float)random(150, 170)) / 10.0;
}