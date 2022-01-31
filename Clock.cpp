#include "Clock.h"
#include <NTPClient.h>
#include <WiFiNINA.h>

WiFiUDP ntpUDP;
NTPClient ntpClient(ntpUDP);


void Clock::begin(){
    ntpClient.begin();
}

unsigned long Clock::now(){
 // Update time via NTP if required
  while (!ntpClient.update()) {
    yield();
    ntpClient.forceUpdate();
  }
  // Get current timestamp
  unsigned long ts = ntpClient.getEpochTime();
  return ts;
}