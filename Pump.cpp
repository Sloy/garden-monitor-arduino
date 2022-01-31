#include "Pump.h"

#include "Arduino.h"
#include "config.h"

Pump::Pump() {
    // TODO: set pins
}

void Pump::activateFor(int seconds) {
    start();
    delay(seconds * 1000);
    stop();
}

void Pump::start() {
    // TODO: set pin
    LOGLN("Pump: ON");
}
void Pump::stop() {
    // TODO: set pin
    LOGLN("Pump: OFF");
}