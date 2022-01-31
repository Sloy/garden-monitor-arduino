#ifndef StatsServer_h
#define StatsServer_h

#include "SensorData.h"

class StatsServer {
   public:
    void begin();
    void sendData(SensorData data);
};

#endif