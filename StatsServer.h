#ifndef StatsServer_h
#define StatsServer_h

#include "SensorData.h"

class StatsServer {
   public:
    void begin();
    /**
     * Sends sensor data to the clod. Returns true if successful. False if there is an error. Check Serial log for debugging.
     */
    bool sendData(SensorData data);
};

#endif