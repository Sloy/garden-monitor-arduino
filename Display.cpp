#include "Display.h"

#include <LiquidCrystal.h>

#include "Arduino.h"
#include "config.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void Display::begin() {
    if (DISPLAY_ENABLED) {
        lcd.begin(16, 2);
        lcd.clear();
    }
}
void Display::show(SensorData data) {
    showSensors(data.moisture, data.temperature, data.light);
}

void Display::showSensors(int moisture, float temperature, int light) {
    Serial.print("Moisture=");
    Serial.print(moisture);
    Serial.print("\tTemperature=");
    Serial.print(temperature);
    Serial.print("\tLight=");
    Serial.println(light);
    if (DISPLAY_ENABLED) {
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
}