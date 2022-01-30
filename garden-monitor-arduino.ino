#include "Display.h"
#include "Sensors.h"
#include "config.h"
#include "secrets.h"

Sensors sensors(MOISTURE_PIN, TEMPERATURE_PIN, LIGHT_PIN);
Display display(DISPLAY_ENABLED);

void setup() {
    Serial.begin(9600);
    Serial.println("Monitoring ...");
    display.begin();
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    SensorData data = sensors.read();
    display.show(data);
    blink();
    delay(1000);
}

void blink() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
}
