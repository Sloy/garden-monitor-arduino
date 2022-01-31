#ifndef config_h
#define config_h

#include "Arduino.h"
#include "secrets.h"

#define SENSOR_NAME "test"        // Add unique name for this sensor
#define INTERVAL_SECONDS 60       // Add measurement interval (e.g. 1 min)
#define MOISTURE_THREADSHOLD 70  // Moisture % at which we should water the plants
#define PUMP_DURATION 5           // Number of seconds to run the pump for watering

#define MOISTURE_POWER 7    // Which pin is soil moisture sensor connected to as a source of power (prevents fast corrosioon)
#define MOISTURE_PIN A0     // Which pin is soil moisture sensor connected to
#define TEMPERATURE_PIN A1  // Which pin is temperature sensor connected to
#define LIGHT_PIN A2        // Which pin is photoresistor connected to

#define LOGGER true            // Enable logging messages through Serial
#define WAIT_FOR_LOGGER false   // Stops execution until there is a Serial connection for logging
#define RGB_LED true           // Enable the MK1010 board RGB led for status indication
#define DISPLAY_ENABLED false  // Whether the LCD screen is connected to show sensor data
#define FAKE_SENSOR true       // Emit fake sensor data to test the code without connecting all sensors

#define GRAFANA_SERVER "graphite-prod-01-eu-west-0.grafana.net"

#if LOGGER
#define LOG(x) Serial.print(x)
#define LOGLN(x) Serial.println(x)
#else
#define LOG(x)
#define LOGLN(x)
#endif

#endif