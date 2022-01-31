#include "WiFiLed.h"

#include <Arduino.h>
#include <WiFiNINA.h>
#include <utility/wifi_drv.h>

#define RED_PIN 25
#define GREEN_PIN 26
#define BLUE_PIN 27

WiFiLed::WiFiLed(float brightness) {
    _brightness = brightness;
}

void WiFiLed::set(uint8_t red, uint8_t green, uint8_t blue) {
    WiFiDrv::pinMode(RED_PIN, OUTPUT);
    WiFiDrv::pinMode(GREEN_PIN, OUTPUT);
    WiFiDrv::pinMode(BLUE_PIN, OUTPUT);

    WiFiDrv::analogWrite(RED_PIN, red * _brightness);
    WiFiDrv::analogWrite(GREEN_PIN, green * _brightness);
    WiFiDrv::analogWrite(BLUE_PIN, blue * _brightness);
}

void WiFiLed::off(){
    set(0, 0, 0);
}

void WiFiLed::setRed() {
    set(255, 0, 0);
}
void WiFiLed::setGreen() {
    set(0, 255, 0);
}
void WiFiLed::setBlue() {
    set(0, 0, 255);
}
void WiFiLed::setPurple() {
    set(177, 3, 252);
}
void WiFiLed::setPink() {
    set(250, 22, 189);
}
void WiFiLed::setCyan() {
    set(77, 221, 250);
}