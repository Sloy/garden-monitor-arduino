#ifndef Pump_h
#define Pump_h

#include "SensorData.h"

class Pump {
   public:
    Pump();
    void activateFor(int seconds);

   private:
    void start();
    void stop();
};

#endif
