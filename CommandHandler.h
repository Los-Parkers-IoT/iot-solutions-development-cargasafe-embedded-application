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
    // Inicialización opcional (por ejemplo, iniciar Serial o comunicación)
  }

  virtual void handleCommand(const String& command) {
    // Lógica genérica para interpretar comandos
    Serial.println("[CommandHandler] Comando recibido: " + command);
  }
};

#endif
