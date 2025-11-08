#include "GPSSensor.h"

GPSSensor::GPSSensor(HardwareSerial* hwSerial, int rx, int tx, EventHandler* handler)
  : Sensor(rx, handler), serial(hwSerial), txPin(tx) {}

void GPSSensor::begin() {
  serial->begin(9600, SERIAL_8N1, pin, txPin);
  Serial.println("[GPS] Inicializado");
}

void GPSSensor::read() {
  while (serial->available()) {
    gps.encode(serial->read());
  }

  if (gps.location.isUpdated()) {
    String data = "Lat: " + String(gps.location.lat(), 6) +
                  " | Lng: " + String(gps.location.lng(), 6);
    on(Event(EVENT_GPS_UPDATE, data));
  }
}
