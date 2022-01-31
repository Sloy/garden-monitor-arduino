#include "StatsServer.h"

#include <Arduino.h>
#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>

#include "Clock.h"
#include "config.h"

char ssid[] = WIFI_SSID;      // your network SSID (name)
char pass[] = WIFI_PASSWORD;  // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;  // the Wifi radio's status
char serverAddress[] = GRAFANA_SERVER;

WiFiSSLClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, 443);
Clock clock;

void StatsServer::begin() {
    while (status != WL_CONNECTED) {
        LOG("Attempting to connect to Network named: ");
        LOGLN(ssid);
        status = WiFi.begin(ssid, pass);
    }
    LOGLN("Connected!");
    LOG("- SSID: ");
    LOGLN(WiFi.SSID());
    LOG("- IP Address: ");
    LOGLN(WiFi.localIP());

    clock.begin();
}

bool StatsServer::sendData(SensorData data) {
    String endpoint = "/graphite/metrics";
    int ts = clock.now();
    String body = String("[") +
                  "{\"name\":\"" + SENSOR_NAME + ".temperature\",\"interval\":" + INTERVAL_SECONDS + ",\"value\":" + data.temperature + ",\"time\":" + ts + "}," +
                  "{\"name\":\"" + SENSOR_NAME + ".moisture\",\"interval\":" + INTERVAL_SECONDS + ",\"value\":" + data.moisture + ",\"time\":" + ts + "}," +
                  "{\"name\":\"" + SENSOR_NAME + ".light\",\"interval\":" + INTERVAL_SECONDS + ",\"value\":" + data.light + ",\"time\":" + ts + "}]";

    LOG("-> POST ");
    LOG(endpoint);
    LOG("\t");
    LOGLN(body);

    client.beginRequest();
    client.post(endpoint);
    client.sendBasicAuth(GRAPHITE_USER, GRAPHITE_API_KEY);
    client.sendHeader("Content-Type", "application/json");
    client.sendHeader("Content-Length", body.length());
    client.beginBody();
    client.print(body);
    client.endRequest();

    // read the status code and body of the response
    int statusCode = client.responseStatusCode();
    String response = client.responseBody();

    LOG("<- POST ");
    LOG(status);
    LOG("\t");
    LOGLN(response);

    return statusCode >= 200 & statusCode < 300;
}
