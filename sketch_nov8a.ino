#include "ModestIoT.h"
#include "EdgeCommunicatorHttp.h"

#define RXD2 16
#define TXD2 17
#define DHTPIN 25

const char* WIFI_SSID = "IntroduzcaWIFI";
const char* WIFI_PASS = "IntroduzcaContraseña";

const char* EDGE_URL = "https://iot-solutions-development-cargasafe-edge.onrender.com/api/v1/telemetry-monitoring/data-records";

HardwareSerial neogps(1);
EdgeCommunicatorHttp edge(WIFI_SSID, WIFI_PASS, EDGE_URL);
DataController controller(&edge);

GPSSensor gps(&neogps, RXD2, TXD2, &controller);
DHTSensor dht(DHTPIN, &controller);

unsigned long lastReadDHT = 0;
unsigned long lastReadGPS = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("=== Modest IoT Framework (HTTP MODE) ===");

  edge.begin();

  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("Sincronizando hora NTP...");
  delay(1000); 

  gps.begin();
  dht.begin();

  Serial.println("Sensores inicializados correctamente.\n");
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
