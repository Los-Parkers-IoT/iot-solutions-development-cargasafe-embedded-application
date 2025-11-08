#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "EventHandler.h"

/**
 * @class Controller
 * @brief Clase base para todos los controladores del framework Modest IoT.
 */
class Controller : public EventHandler {
public:
  /**
   * @brief Inicializa el controlador.
   */
  virtual void begin() {}

  /**
   * @brief Maneja un evento. Debe ser implementado por las subclases.
   * @param event Evento recibido.
   */
  virtual void on(Event event) override = 0;
};

#endif // CONTROLLER_H
