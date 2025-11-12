/**
 * @file Event.h
 * @brief Defines the Event structure and event types for the Modest IoT Nano-framework.
 * 
 * This file provides the event communication model between sensors, controllers,
 * and the core of the Modest IoT system.
 * 
 * @author Daniel
 * @date November 08, 2025
 */

#ifndef EVENT_H
#define EVENT_H

#include <Arduino.h>

/**
 * @brief Enumerates possible event types.
 */
enum EventType {
  EVENT_NONE = 0,
  EVENT_GPS_UPDATE,
  EVENT_DHT_UPDATE,
  EVENT_ERROR
};

/**
 * @brief Represents an event emitted by a sensor or system component.
 */
struct Event {
  EventType type;    
  String message;    

  Event(EventType t = EVENT_NONE, String msg = "")
    : type(t), message(msg) {}
};

#endif 
