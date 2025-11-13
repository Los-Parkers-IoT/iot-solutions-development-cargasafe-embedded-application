#include "DHTSensor.h"

DHTSensor::DHTSensor(int pin, EventHandler* handler)
  : Sensor(pin, handler), dht(pin, DHT11), lastTemperature(0.0), lastHumidity(0.0) {}

void DHTSensor::begin() {
  dht.begin();
  Serial.println("[DHT11] Initialized");
}

void DHTSensor::read() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    on(Event(EVENT_ERROR, "Error reading DHT11"));
  } else {
    lastHumidity = h;
    lastTemperature = t;
    
    String data = "Temp: " + String(t) + " °C | Hum: " + String(h) + " %";
    on(Event(EVENT_DHT_UPDATE, data));
  }
}

float DHTSensor::getTemperature() {
  return lastTemperature;
}

float DHTSensor::getHumidity() {
  return lastHumidity;
}
