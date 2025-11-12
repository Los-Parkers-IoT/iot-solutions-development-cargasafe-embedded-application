#include "ModestIoT.h"
#include "EdgeCommunicatorHttp.h"

#define RXD2 16
#define TXD2 17
#define DHTPIN 25

const char* WIFI_SSID = "WIFI";
const char* WIFI_PASS = "Password";

const char* EDGE_URL = "http://192.168.1.47:5000/api/v1/telemetry-monitoring/data-records";

HardwareSerial neogps(1);
EdgeCommunicatorHttp edge(WIFI_SSID, WIFI_PASS, EDGE_URL);
DataController controller(&edge);

GPSSensor gps(&neogps, RXD2, TXD2, &controller);
DHTSensor dht(DHTPIN, &controller);

unsigned long lastReadDHT = 0;
unsigned long lastReadGPS = 0;

void setup() {
  Serial.begin(115200);

  edge.begin();

  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("Synchronizing NTP time...");
  delay(1000); 

  gps.begin();
  dht.begin();

  Serial.println("Sensors initialized successfully.\n");
}

void loop() {
  unsigned long now = millis();

  if (now - lastReadGPS >= 2000) {
    gps.read();
    lastReadGPS = now;
  }

  if (now - lastReadDHT >= 3000) {
    dht.read();
    lastReadDHT = now;
  }
}
