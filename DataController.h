#ifndef DATA_CONTROLLER_H
#define DATA_CONTROLLER_H

#include "EventHandler.h"

/**
 * @class DataController
 * @brief Controlador que recibe y procesa eventos de sensores.
 */
class DataController : public EventHandler {
public:
  /**
   * @brief Maneja los eventos emitidos por los sensores.
   * @param event Evento recibido.
   */
  void on(Event event) override {
    Serial.println("------------------------------");
    switch (event.type) {
      case EVENT_GPS_UPDATE:
        Serial.println("Evento: GPS UPDATE");
        Serial.println(event.message);
        break;

      case EVENT_DHT_UPDATE:
        Serial.println("Evento: DHT UPDATE");
        Serial.println(event.message);
        break;

      case EVENT_ERROR:
        Serial.println("Evento: ERROR");
        Serial.println(event.message);
        break;

      default:
        Serial.println("Evento desconocido");
        break;
    }
    Serial.println("------------------------------\n");
  }
};

#endif // DATA_CONTROLLER_H
