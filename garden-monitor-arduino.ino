#include "Display.h"
#include "Sensors.h"
#include "StatsServer.h"
#include "config.h"

Sensors sensors;
Display display;
StatsServer server;

void setup() {
    Serial.begin(9600);
    Serial.println("Monitoring ...");
    display.begin();
    server.begin();
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    ledIndicator(true);
    SensorData data = sensors.read();
    display.show(data);
    server.sendData(data);
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
