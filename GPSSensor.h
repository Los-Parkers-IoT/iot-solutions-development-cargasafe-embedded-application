#ifndef GPS_SENSOR_H
#define GPS_SENSOR_H

#include "Sensor.h"
#include <TinyGPS++.h>
#include <HardwareSerial.h>

/**
 * @class GPSSensor
 * @brief Class responsible for handling the GPS sensor.
 */
class GPSSensor : public Sensor {
private:
  HardwareSerial* serial; 
  TinyGPSPlus gps;        
  int txPin;             

public:
  /**
  * @brief GPS sensor constructor
  * @param hwSerial Pointer to the hardware serial port
  * @param rx GPS RX pin
  * @param tx GPS TX pin
  
*/
  GPSSensor(HardwareSerial* hwSerial, int rx, int tx, EventHandler* handler = nullptr);

  /**
   * @brief Initialize the GPS module
   */
  void begin() override;

  /**
   * @brief Reads GPS data and generates events when there is a new location.
   */
  void read() override;
};

#endif
