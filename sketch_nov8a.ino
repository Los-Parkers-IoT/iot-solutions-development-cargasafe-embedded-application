#include "ModestIoT.h"

#define RXD2 16
#define TXD2 17
#define DHTPIN 25

HardwareSerial neogps(1);
DataController controller;

GPSSensor gps(&neogps, RXD2, TXD2, &controller);
DHTSensor dht(DHTPIN, &controller);

unsigned long lastReadDHT = 0;
unsigned long lastReadGPS = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("=== Modest IoT Framework ===");

  gps.begin();
  dht.begin();

  Serial.println("Sensores inicializados correctamente.\n");
}

void loop() {
  unsigned long now = millis();

  if (now - lastReadGPS >= 1000) {
    gps.read();
    lastReadGPS = now;
  }

  if (now - lastReadDHT >= 2000) {
    dht.read();
    lastReadDHT = now;
  }
}
