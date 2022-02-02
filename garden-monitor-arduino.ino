#include "Display.h"
#include "Pump.h"
#include "Sensors.h"
#include "StatsServer.h"
#include "WiFiLed.h"
#include "config.h"

Sensors sensors;
Display display;
StatsServer server;
WiFiLed led(0.01);
Pump pump;

void setup() {
    led.setPurple();
#if LOGGER
    Serial.begin(9600);
#if WAIT_FOR_LOGGER
    while (!Serial)
        ;
#endif
#endif
    LOGLN("Setup ...");
    led.setBlue();
    display.begin();
    server.begin();
    server.log("Boot", "Boot");
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    ledIndicator(true);

    // Read data
    SensorData data = sensors.read();
    display.show(data);

    // Publish data
    bool success = server.sendData(data);
    ledStatus(success);

    waterPump(data);

    ledIndicator(false);
    delay(INTERVAL_SECONDS * 1000);
}

void waterPump(SensorData data) {
    if (PUMP) {
        delay(1000);  // For debugging status led
        // Should we water?
        if (data.moisture < MOISTURE_THREADSHOLD) {
            // Run pump
            server.reportPump(true);
            server.log("PUMP", "Pump ON");
            led.setCyan();
            pump.activateFor(PUMP_DURATION);
            server.log("PUMP", "Pump OFF");

            // Is it wet?
            data = sensors.read();
            server.sendData(data);
            led.setGreen();
            bool isDry = data.moisture < MOISTURE_THREADSHOLD;
            if (isDry) {
                //repeat? or error?
                LOGLN("(PUMP) W: Still dry after watering. What to do, take a poo");
                server.log("PUMP", "W: Still dry");
                led.setOrange();
            }
        }
    }
}

void ledStatus(bool success) {
    if (success) {
        led.setGreen();
    } else {
        led.setRed();
    }
}

void ledIndicator(bool on) {
    if (on) {
        digitalWrite(LED_BUILTIN, HIGH);
    } else {
        digitalWrite(LED_BUILTIN, LOW);
    }
}
