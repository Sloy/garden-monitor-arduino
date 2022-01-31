#ifndef config_h
#define config_h

#include "Arduino.h"
#include "secrets.h"

#define SENSOR_NAME "test"  // Add unique name for this sensor
#define INTERVAL_SECONDS 3      // Add measurement interval (e.g. 1 min)

#define MOISTURE_POWER 7    // Which pin is soil moisture sensor connected to as a source of power (prevents fast corrosioon)
#define MOISTURE_PIN A0     // Which pin is soil moisture sensor connected to
#define TEMPERATURE_PIN A1  // Which pin is temperature sensor connected to
#define LIGHT_PIN A2        // Which pin is photoresistor connected to

#define DISPLAY_ENABLED false  // Whether the LCD screen is connected to show sensor data
#define FAKE_SENSOR true     // Emit fake sensor data to test the code without connecting all sensors

#define GRAFANA_SERVER "graphite-prod-01-eu-west-0.grafana.net"
//#define GRAFANA_SERVER "02df-79-146-243-222.ngrok.io"

#endif