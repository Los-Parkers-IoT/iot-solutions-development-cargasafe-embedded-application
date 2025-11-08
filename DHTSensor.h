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
 * @brief Clase encargada de manejar el sensor DHT11.
 */
class DHTSensor : public Sensor {
private:
  DHT dht; ///< Instancia del sensor DHT

public:
  /**
   * @brief Constructor del sensor DHT11
   * @param pin Pin donde está conectado el sensor
   * @param handler Manejador de eventos opcional
   */
  DHTSensor(int pin, EventHandler* handler = nullptr);

  /**
   * @brief Inicializa el sensor DHT11
   */
  void begin() override;

  /**
   * @brief Lee temperatura y humedad del sensor y dispara un evento
   */
  void read() override;
};

#endif
