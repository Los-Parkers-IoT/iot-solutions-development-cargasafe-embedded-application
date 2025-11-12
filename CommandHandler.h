#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <Arduino.h>
#include "EventHandler.h"

class CommandHandler {
protected:
  EventHandler* eventHandler;

public:
  CommandHandler(EventHandler* handler = nullptr)
    : eventHandler(handler) {}

  virtual void begin() {
    // Inicializer
  }

  virtual void handleCommand(const String& command) {
    Serial.println("Response: " + command);
  }
};

#endif
