#ifndef StatsServer_h
#define StatsServer_h

#include <Arduino.h>

#include "SensorData.h"

class StatsServer {
   public:
    void begin();
    /**
     * Sends sensor data to the clod. Returns true if successful. False if there is an error. Check Serial log for debugging.
     */
    bool sendData(SensorData data);

    bool reportPump(bool status);

   private:
    /**
     * Returns the status code
     */
    int sendToGraphite(String body);
};

#endif