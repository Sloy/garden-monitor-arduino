#ifndef config_h
#define config_h

#include "Arduino.h"
#include "secrets.h"

#define SENSOR_NAME "test"          // Add unique name for this sensor
#define INTERVAL_SECONDS 20         // Add measurement interval (e.g. 1 min)
#define MOISTURE_THREADSHOLD 70     // Moisture % at which we should water the plants
#define PUMP_DURATION 20            // Number of seconds to run the pump for watering
#define RESET_TIMER_SECONDS 30 * 60  // Time interval at which the board will reset to avoid issues with battery charger timer fault after ~45 min. Set to -1 to disable.

#define MOISTURE_POWER 7    // Which pin is soil moisture sensor connected to as a source of power (prevents fast corrosioon)
#define MOISTURE_PIN A0     // Which pin is soil moisture sensor connected to
#define TEMPERATURE_PIN A1  // Which pin is temperature sensor connected to
#define LIGHT_PIN A2        // Which pin is photoresistor connected to
#define BOARD_VOLTAGE 3.3   // What the operation voltage of the board (3.3, 5.0)

#define LOGGER true            // Enable logging messages through Serial
#define WAIT_FOR_LOGGER false  // Stops execution until there is a Serial connection for logging
#define RGB_LED true           // Enable the MK1010 board RGB led for status indication
#define DISPLAY_ENABLED false  // Whether the LCD screen is connected to show sensor data
#define FAKE_SENSOR false      // Emit fake sensor data to test the code without connecting all sensors
#define SEND_DATA true         // Enables sending data to the clod
#define PUMP false             // Enables the connected pump when the moisture level drops below the threadshold.

#define WAKE_LOCK false        // Workaround when powering from a Power Bank. The Arduino doesn't consume enough power to keep the battery on.
#define WAKE_LOCK_INTERVAL 20  // How many seconds to wait between Wake Lock pings.

#define GRAFANA_SERVER "graphite-prod-01-eu-west-0.grafana.net"
#define LOKI_SERVER "logs-prod-eu-west-0.grafana.net"
#define INFLUXDB_SERVER "eu-central-1-1.aws.cloud2.influxdata.com"

#if LOGGER
#define LOG(x) Serial.print(x)
#define LOGLN(x) Serial.println(x)
#else
#define LOG(x)
#define LOGLN(x)
#endif

#endif