#include "Clock.h"

#include <NTPClient.h>
#include <WiFiNINA.h>

#include "config.h"

WiFiUDP ntpUDP;
NTPClient ntpClient(ntpUDP);

void Clock::begin() {
    ntpClient.begin();
}

unsigned long Clock::now() {
    // Update time via NTP if required
    bool result = ntpClient.update();
    LOGLN(result);
    while (!ntpClient.update()) {
        yield();
        LOGLN("(Clock) Force update");
        ntpClient.forceUpdate();
    }
    // Get current timestamp
    unsigned long ts = ntpClient.getEpochTime();
    return ts;
}