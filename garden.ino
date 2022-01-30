#include "Display.h"
#include "Sensors.h"

Sensors sensors(/* moisture */ A0, /* temperature */ A1, /* light */ A2);
Display display(true);

void setup() {
    Serial.begin(9600);
    Serial.println("Monitoring ...");
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
