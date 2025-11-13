#include "ModestIoT.h"
#include "EdgeCommunicatorHttp.h"

#define RXD2 16
#define TXD2 17
#define DHTPIN 25
#define LED_PIN 12

const char* WIFI_SSID = "WIFI";
const char* WIFI_PASS = "Password";

const char* EDGE_URL = "http://192.168.1.47:5000/api/v1/telemetry-monitoring/data-records";

HardwareSerial neogps(1);
EdgeCommunicatorHttp edge(WIFI_SSID, WIFI_PASS, EDGE_URL);
DataController controller(&edge);

class DHTSensorExtended : public DHTSensor {
public:
  float lastTemp = NAN;
  float lastHum = NAN;

  DHTSensorExtended(int pin, EventHandler* handler = nullptr)
    : DHTSensor(pin, handler) {}

  void read() override {
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      on(Event(EVENT_ERROR, "Error DHT11 is not reading"));
    } else {
      lastTemp = t;
      lastHum = h;

      String data = "Temp: " + String(t) + " °C | Hum: " + String(h) + " %";
      on(Event(EVENT_DHT_UPDATE, data));
    }
  }
};

GPSSensor gps(&neogps, RXD2, TXD2, &controller);
DHTSensor dht(DHTPIN, &controller);

unsigned long lastReadDHT = 0;
unsigned long lastReadGPS = 0;
const float TEMP_THRESHOLD = 28.0;

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

    if (!isnan(dht.lastTemp)) {
      Serial.printf("Temperature: %.2f °C | Humidity: %.2f %%\n", dht.lastTemp, dht.lastHum);

      if (dht.lastTemp > TEMP_THRESHOLD) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("HIGH TEMPERATURE");
      } else {
        digitalWrite(LED_PIN, LOW);
        Serial.println("LOW TEMPERATURE");
      }
    }

    Serial.println("------------------------------");
  }
}
