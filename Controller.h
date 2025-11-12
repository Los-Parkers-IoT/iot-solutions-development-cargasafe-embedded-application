#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "EventHandler.h"

class Controller : public EventHandler {
public:
  /**
   * @brief Initialize the controller.
   */
  virtual void begin() {}

  /**
   * @brief Handles an event. Must be implemented by subclasses.
   * @param event Received event.
   */
  virtual void on(Event event) override = 0;
};

#endif 
