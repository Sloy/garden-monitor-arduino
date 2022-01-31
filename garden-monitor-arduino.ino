#include "Display.h"
#include "Sensors.h"
#include "StatsServer.h"
#include "WiFiLed.h"
#include "config.h"

Sensors sensors;
Display display;
StatsServer server;
WiFiLed led(0.01);

void setup() {
    Serial.begin(9600);
    Serial.println("Monitoring ...");
    led.setBlue();
    display.begin();
    server.begin();
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    ledIndicator(true);
    SensorData data = sensors.read();
    display.show(data);
    bool success = server.sendData(data);
    if (success) {
        led.setGreen();
    } else {
        led.setRed();
    }
    ledIndicator(false);
    delay(INTERVAL_SECONDS * 1000);
}

void ledIndicator(bool on) {
    if (on) {
        digitalWrite(LED_BUILTIN, HIGH);
    } else {
        digitalWrite(LED_BUILTIN, LOW);
    }
}
