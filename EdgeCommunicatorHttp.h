#ifndef EDGE_COMMUNICATOR_HTTP_H
#define EDGE_COMMUNICATOR_HTTP_H

#include <WiFi.h>
#include <HTTPClient.h>
#include "Event.h"

class EdgeCommunicatorHttp {
private:
  const char* ssid;
  const char* password;
  const char* url;

public:
  EdgeCommunicatorHttp(const char* ssid,
                       const char* password,
                       const char* url);

  void begin();
  void sendEvent(const Event& event);
  void postJson(const String& json);
};

#endif
