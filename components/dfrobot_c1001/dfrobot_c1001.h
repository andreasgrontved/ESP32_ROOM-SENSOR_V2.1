#pragma once

#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"
#include "DFRobot_HumanDetection.h"

namespace esphome {

class DFRobotC1001 : public uart::UARTDevice, public Component {
 public:
  explicit DFRobotC1001(uart::UARTComponent *parent);
  void setup() override;
  void loop() override;

  // Sensors
  Sensor *presence_sensor = new Sensor();
  Sensor *motion_sensor = new Sensor();
  Sensor *movement_param_sensor = new Sensor();
  Sensor *respiration_rate_sensor = new Sensor();
  Sensor *heart_rate_sensor = new Sensor();

 private:
  DFRobot_HumanDetection hu_;  // Library instance
};

}  // namespace esphome
