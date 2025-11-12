/**
 * @file DHTSensor.h
 * @brief Temperature & Humidity Sensor (DHT11)
 * @author Daniel Arevalo
 * @date November 08, 2025
 */

#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include "Sensor.h"
#include <DHT.h>

/**
 * @class DHTSensor
 * @brief Class responsible for managing the DHT11 sensor.
 */
class DHTSensor : public Sensor {
private:
  DHT dht; 

public:
  /**
   * @brief DHT11 sensor constructor
   * @param pin Pin where the sensor is connected
   * @param handler Optional event handler
   */
  DHTSensor(int pin, EventHandler* handler = nullptr);

  /**
   * @brief Initialize the DHT11 sensor
   */
  void begin() override;

  /**
   * @brief Reads temperature and humidity from the sensor and triggers an event
   */
  void read() override;
};

#endif
