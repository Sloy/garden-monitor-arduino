
/*

*/

#include <LiquidCrystal.h>

#include "Sensors.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Sensors sensors(/* moisture */ A0, /* temperature */ A1, /* light */ A2);

void setup() {
    Serial.begin(9600);
    Serial.println("Monitoring ...");
    lcd.begin(16, 2);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    int moisture = sensors.readMoisture();
    int light = sensors.readLight();
    float temperature = sensors.readTemperature();
    printValues(moisture, light, temperature);
    blink();
    delay(1000);
}

void printValues(int moisture, int light, float temperature) {
    //Serial.println("Printing values: Moisture=" + moisture);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Agua ");
    lcd.print(moisture);
    lcd.print("% Luz ");
    lcd.print(light);
    lcd.print("% ");
    lcd.setCursor(0, 1);
    lcd.print("Temp ");
    lcd.print(temperature, 1);
    lcd.print((char)223);
    lcd.print("C");
}

void blink() {
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(50);                        // wait for a second
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    delay(50);
}
