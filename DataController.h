#ifndef DATA_CONTROLLER_H
#define DATA_CONTROLLER_H

#include "EventHandler.h"
#include "EdgeCommunicatorHttp.h"

/**
 * @class DataController
 * @brief Controller that receives and processes sensor events.
 */
class DataController : public EventHandler {
private:
  EdgeCommunicatorHttp* edge;

public:
  DataController(EdgeCommunicatorHttp* edgeClient = nullptr)
    : edge(edgeClient) {}

  void on(Event event) override {
    Serial.println("------------------------------");

    switch (event.type) {
      case EVENT_GPS_UPDATE:
        Serial.println("Event: GPS UPDATE");
        Serial.println(event.message);
        break;

      case EVENT_DHT_UPDATE:
        Serial.println("Event: DHT UPDATE");
        Serial.println(event.message);
        break;

      case EVENT_ERROR:
        Serial.println("Event: ERROR");
        Serial.println(event.message);
        break;
    }

    Serial.println("------------------------------\n");

    if (edge) {
      edge->sendEvent(event);
    }
  }
};

#endif 
