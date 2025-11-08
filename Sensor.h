#ifndef SENSOR_H
#define SENSOR_H

#include "EventHandler.h"

class Sensor : public EventHandler {
protected:
  int pin;
  EventHandler* handler;

public:
  Sensor(int pin, EventHandler* handler = nullptr)
      : pin(pin), handler(handler) {}

  virtual void begin() = 0;
  virtual void read() = 0;

  void setHandler(EventHandler* h) { handler = h; }

  void on(Event event) override {
    if (handler) handler->on(event);
  }
};

#endif
