#include "Display.h"
#include "Sensors.h"
#include "config.h"
#include "secrets.h"

Sensors sensors;
Display display(DISPLAY_ENABLED);

void setup() {
    Serial.begin(9600);
    Serial.println("Monitoring ...");
    display.begin();
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    ledIndicator(true);
    SensorData data = sensors.read();
    display.show(data);
    ledIndicator(false);
    delay(INTERVAL_SECONDS * 1000);
}

void ledIndicator(bool on) {
    delay(100);
    if (on) {
        digitalWrite(LED_BUILTIN, HIGH);
    } else {
        digitalWrite(LED_BUILTIN, LOW);
    }
}
