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
    int moisture = sensors.readMoisture();
    int light = sensors.readLight();
    float temperature = sensors.readTemperature();
    display.showSensors(moisture, temperature, light);
    blink();
    delay(1000);
}

void blink() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
}
