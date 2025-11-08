#include "DHTSensor.h"

DHTSensor::DHTSensor(int pin, EventHandler* handler)
  : Sensor(pin, handler), dht(pin, DHT11) {}

void DHTSensor::begin() {
  dht.begin();
  Serial.println("[DHT11] Inicializado");
}

void DHTSensor::read() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    on(Event(EVENT_ERROR, "Error al leer DHT11"));
  } else {
    String data = "Temp: " + String(t) + " °C | Hum: " + String(h) + " %";
    on(Event(EVENT_DHT_UPDATE, data));
  }
}
