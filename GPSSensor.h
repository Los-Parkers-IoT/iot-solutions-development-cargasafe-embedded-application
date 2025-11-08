/**
 * @file GPSSensor.h
 * @brief GPS Sensor (Neo-6M compatible)
 * @author Daniel Arevalo
 * @date November 08, 2025
 */

#ifndef GPS_SENSOR_H
#define GPS_SENSOR_H

#include "Sensor.h"
#include <TinyGPS++.h>
#include <HardwareSerial.h>

/**
 * @class GPSSensor
 * @brief Clase encargada de manejar el sensor GPS (Neo-6M).
 */
class GPSSensor : public Sensor {
private:
  HardwareSerial* serial; ///< Puerto serial usado por el GPS
  TinyGPSPlus gps;        ///< Instancia del parser GPS
  int txPin;              ///< Pin TX del GPS

public:
  /**
   * @brief Constructor del sensor GPS
   * @param hwSerial Puntero al puerto serial de hardware (por ejemplo, &Serial1)
   * @param rx Pin RX del GPS
   * @param tx Pin TX del GPS
   * @param handler Manejador de eventos opcional
   */
  GPSSensor(HardwareSerial* hwSerial, int rx, int tx, EventHandler* handler = nullptr);

  /**
   * @brief Inicializa el módulo GPS
   */
  void begin() override;

  /**
   * @brief Lee datos del GPS y genera eventos cuando hay nueva ubicación
   */
  void read() override;
};

#endif
