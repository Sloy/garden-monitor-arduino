#include "Display.h"

#include <LiquidCrystal.h>

#include "Arduino.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Display::Display(bool enabled) {
    _enabled = enabled;
}
void Display::begin() {
    if (_enabled) {
        lcd.begin(16, 2);
        lcd.clear();
    }
}
void Display::show(SensorData data) {
    showSensors(data.moisture, data.temperature, data.light);
}

void Display::showSensors(int moisture, float temperature, int light) {
    if (_enabled) {
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