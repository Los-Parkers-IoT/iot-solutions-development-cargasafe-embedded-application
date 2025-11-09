#include "EdgeCommunicatorHttp.h"
#include <time.h>

String getISOTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return "1970-01-01T00:00:00Z";
  }

  char buffer[30];
  strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);
  return String(buffer);
}


EdgeCommunicatorHttp::EdgeCommunicatorHttp(const char* ssid,
                                           const char* password,
                                           const char* url)
  : ssid(ssid), password(password), url(url) {}

void EdgeCommunicatorHttp::begin() {
  Serial.println("[HTTP] Conectando a WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n[HTTP] WiFi conectado.");
}

void EdgeCommunicatorHttp::postJson(const String& json) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[HTTP] WiFi desconectado.");
    return;
  }

  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/json");

  int code = http.POST(json);
  Serial.print("[HTTP] POST -> Código: ");
  Serial.println(code);

  if (code > 0) {
    Serial.println("[HTTP] Respuesta:");
    Serial.println(http.getString());
  }

  http.end();
}

void EdgeCommunicatorHttp::sendEvent(const Event& event) {
  String json = "{";

  json += "\"device_id\":\"cargasafe-01\",";

  if (event.type == EVENT_GPS_UPDATE) {
    int latPos = event.message.indexOf("Lat: ") + 5;
    int sepPos = event.message.indexOf("|");
    int lngPos = event.message.indexOf("Lng: ") + 5;

    String lat = event.message.substring(latPos, sepPos);
    String lng = event.message.substring(lngPos);

    json += "\"latitude\":" + lat + ",";
    json += "\"longitude\":" + lng + ",";
    json += "\"temperature\":0,";
    json += "\"humidity\":0";

  } else if (event.type == EVENT_DHT_UPDATE) {
    int tPos = event.message.indexOf("Temp: ") + 6;
    int cPos = event.message.indexOf(" °C");
    int hPos = event.message.indexOf("Hum: ") + 5;
    int pPos = event.message.indexOf(" %");

    String temp = event.message.substring(tPos, cPos);
    String hum = event.message.substring(hPos, pPos);

    json += "\"temperature\":" + temp + ",";
    json += "\"humidity\":" + hum + ",";
    json += "\"latitude\":0,";
    json += "\"longitude\":0";
  }

  String isoTime = getISOTime();
  json += ",\"created_at\":\"" + isoTime + "\"}";

  Serial.println("[HTTP] Enviando JSON:");
  Serial.println(json);

  postJson(json);
}


