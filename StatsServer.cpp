#include "StatsServer.h"

#include <Arduino.h>
#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>

#include "Clock.h"
#include "config.h"

#define STATUS_ON 1
#define STATUS_OFF 0
#define STATUS_ERROR -1

char ssid[] = WIFI_SSID;      // your network SSID (name)
char pass[] = WIFI_PASSWORD;  // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;  // the Wifi radio's status

WiFiSSLClient wifi;
HttpClient client = HttpClient(wifi, GRAFANA_SERVER, 443);
HttpClient lokiClient = HttpClient(wifi, LOKI_SERVER, 443);
HttpClient influxClient = HttpClient(wifi, INFLUXDB_SERVER, 443);
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
    int ts = clock.now();
    int statusCode = sendToGraphite(data, ts);
    statusCode = sendToInfluxDB(data, ts);

    return statusCode >= 200 & statusCode < 300;
}

bool StatsServer::reportPump(bool pumpStatus) {
    /*
    int ts = clock.now();
    int value, interval;
    if (pumpStatus) {
        value = STATUS_ON;
        interval = PUMP_DURATION;
    } else {
        value = STATUS_OFF;
        interval = 1;
    }
    String body = String("[") +
                  "{\"name\":\"" + SENSOR_NAME + ".pump\",\"interval\":" + interval + ",\"value\":" + value + ",\"time\":" + ts + "}]";

    int statusCode = sendToGraphite(body);
    return statusCode >= 200 & statusCode < 300;
    */
}

int StatsServer::sendToGraphite(SensorData data, int timestamp) {
    if (!SEND_DATA) {
        return 200;
    }
    String body = String("[") +
                  "{\"name\":\"" + SENSOR_NAME + ".temperature\",\"interval\":" + INTERVAL_SECONDS + ",\"value\":" + data.temperature + ",\"time\":" + timestamp + "}," +
                  "{\"name\":\"" + SENSOR_NAME + ".moisture\",\"interval\":" + INTERVAL_SECONDS + ",\"value\":" + data.moisture + ",\"time\":" + timestamp + "}," +
                  "{\"name\":\"" + SENSOR_NAME + ".battery\",\"interval\":" + INTERVAL_SECONDS + ",\"value\":" + data.batteryVoltage + ",\"time\":" + timestamp + "}," +
                  "{\"name\":\"" + SENSOR_NAME + ".light\",\"interval\":" + INTERVAL_SECONDS + ",\"value\":" + data.light + ",\"time\":" + timestamp + "}]";
    String endpoint = "/graphite/metrics";
    LOGLN("-------------");
    LOG("-> POST ");
    LOG(endpoint);
    LOG("\t\t\t\t");
    LOGLN(body);

    client.beginRequest();
    client.post(endpoint);
    client.sendBasicAuth(GRAPHITE_USER, GRAFANA_API_KEY);
    client.sendHeader("Content-Type", "application/json");
    client.sendHeader("Content-Length", body.length());
    client.beginBody();
    client.print(body);
    client.endRequest();

    // read the status code and body of the response
    int statusCode = client.responseStatusCode();
    String response = client.responseBody();

    LOG("<- POST ");
    LOG(statusCode);
    LOG("\t\t\t\t");
    LOGLN(response);
    LOGLN("-------------");

    return statusCode;
}

int StatsServer::sendToInfluxDB(SensorData data, int timestamp) {
    if (!SEND_DATA) {
        return 200;
    }
    String body = String("sensor temperature=") + data.temperature + ",moisture="+data.moisture+",light="+data.light+",battery="+data.batteryVoltage;
    String endpoint = String("/api/v2/write?org=") + INFLUX_ORG_ID + "&bucket=" + INFLUX_BUCKET + "&precision=s";
    ;
    LOGLN("-------------");
    LOG("-> POST ");
    LOG(endpoint);
    LOG("\t\t\t\t");
    LOGLN(body);

    influxClient.beginRequest();
    influxClient.post(endpoint);
    influxClient.sendHeader("Content-Type", "text/plain");
    influxClient.sendHeader("Content-Length", body.length());
    influxClient.sendHeader("Authorization", INFLUX_TOKEN);
    influxClient.beginBody();
    influxClient.print(body);
    influxClient.endRequest();

    // read the status code and body of the response
    int statusCode = influxClient.responseStatusCode();
    String response = influxClient.responseBody();

    LOG("<- POST ");
    LOG(statusCode);
    LOG("\t\t\t\t");
    LOGLN(response);
    LOGLN("-------------");

    return statusCode;
}

bool StatsServer::log(String tag, String message) {
    if (!SEND_DATA) {
        return 200;
    }
    int ts = clock.now();
    String endpoint = "/loki/api/v1/push";
    String body = String("{\"streams\": [{ \"stream\": { \"label\": \"") +
                  "" + SENSOR_NAME + "\"}, \"values\": [ [ \"" + ts + "000000000\", \"" + message + "\" ] ] }]}";

    LOGLN("-------------");
    LOG("-> POST ");
    LOG(endpoint);
    LOG("\t\t\t\t");
    LOGLN(body);

    lokiClient.beginRequest();
    lokiClient.post(endpoint);
    lokiClient.sendBasicAuth(LOKI_USER, GRAFANA_API_KEY);
    lokiClient.sendHeader("Content-Type", "application/json");
    lokiClient.sendHeader("Content-Length", body.length());
    lokiClient.beginBody();
    lokiClient.print(body);
    lokiClient.endRequest();

    // read the status code and body of the response
    int statusCode = lokiClient.responseStatusCode();
    String response = lokiClient.responseBody();

    LOG("<- POST ");
    LOG(statusCode);
    LOG("\t\t\t\t");
    LOGLN(response);
    LOGLN("-------------");

    return statusCode;
}