#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "DFRobot_HumanDetection.h"  // Include your sensor library

namespace esphome {
namespace dfrobot_c1001 {

class DFRobotC1001 : public uart::UARTDevice, public Component {
 public:
  // Constructor
  DFRobotC1001(uart::UARTComponent *parent);

  // Component lifecycle methods
  void setup() override;
  void loop() override;
  void dump_config() override;

  // Sensors to expose
  binary_sensor::BinarySensor *presence_binary_sensor = new binary_sensor::BinarySensor();
  sensor::Sensor *motion_sensor = new sensor::Sensor();
  sensor::Sensor *movement_param_sensor = new sensor::Sensor();
  sensor::Sensor *respiration_rate_sensor = new sensor::Sensor();
  sensor::Sensor *heart_rate_sensor = new sensor::Sensor();

 private:
  // Instance of your sensor class
  DFRobot_HumanDetection hu_;
};

}  // namespace dfrobot_c1001
}  // namespace esphome
