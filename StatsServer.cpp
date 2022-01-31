#include "StatsServer.h"
#include "Clock.h"

#include <Arduino.h>
#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>

#include "config.h"

char ssid[] = WIFI_SSID;      // your network SSID (name)
char pass[] = WIFI_PASSWORD;  // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;  // the Wifi radio's status
char serverAddress[] = "graphite-us-central1.grafana.net";

WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, 443);
Clock clock;

void StatsServer::begin() {
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to Network named: ");
        Serial.println(ssid);  // print the network name (SSID);

        // Connect to WPA/WPA2 network:
        status = WiFi.begin(ssid, pass);
    }
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    clock.begin();
}

void StatsServer::sendData(SensorData data) {
    Serial.println("making POST request");
    String contentType = "application/json";
    int ts = clock.now();
    String body = String("[") +
                  "{\"name\":\"temperature\",\"interval\":" + INTERVAL_SECONDS + ",\"value\":" + data.temperature + ",\"mtype\":\"gauge\",\"time\":" + ts + "}," +
                  "{\"name\":\"moisture\",\"interval\":" + INTERVAL_SECONDS + ",\"value\":" + data.moisture + ",\"mtype\":\"gauge\",\"time\":" + ts + "}," +
                  "{\"name\":\"light\",\"interval\":" + INTERVAL_SECONDS + ",\"value\":" + data.light + ",\"mtype\":\"gauge\",\"time\":" + ts + "}]";

    client.beginRequest();
    client.post("/metrics");
    client.sendBasicAuth(GRAPHITE_USER, GRAPHITE_API_KEY);
    client.endRequest();

    // read the status code and body of the response
    int statusCode = client.responseStatusCode();
    String response = client.responseBody();

    Serial.print("Status code: ");
    Serial.println(statusCode);
    Serial.print("Response: ");
    Serial.println(response);
}