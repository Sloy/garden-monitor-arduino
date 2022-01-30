#include "Arduino.h"

#define SENSOR_NAME "albahaca"  // Add unique name for this sensor
#define INTERVAL_SECONDS 60     // Add measurement interval (e.g. 1 min)

#define MOISTURE_POWER 7   // Which pin is soil moisture sensor connected to as a source of power (prevents fast corrosioon)
#define MOISTURE_PIN A0     // Which pin is soil moisture sensor connected to
#define TEMPERATURE_PIN A1  // Which pin is temperature sensor connected to
#define LIGHT_PIN A2        // Which pin is photoresistor connected to

#define DISPLAY_ENABLED true // Whether the LCD screen is connected to show sensor data
