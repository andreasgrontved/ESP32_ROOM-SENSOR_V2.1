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

  // Methods to set sensors
  void set_presence_sensor(sensor::Sensor *presence_sensor) { presence_sensor_ = presence_sensor; }
  void set_motion_sensor(sensor::Sensor *motion_sensor) { motion_sensor_ = motion_sensor; }
  void set_movement_param_sensor(sensor::Sensor *movement_param_sensor) { movement_param_sensor_ = movement_param_sensor; }
  void set_respiration_rate_sensor(sensor::Sensor *respiration_rate_sensor) { respiration_rate_sensor_ = respiration_rate_sensor; }
  void set_heart_rate_sensor(sensor::Sensor *heart_rate_sensor) { heart_rate_sensor_ = heart_rate_sensor; }

 private:
  sensor::Sensor *presence_sensor_{nullptr};
  sensor::Sensor *motion_sensor_{nullptr};
  sensor::Sensor *movement_param_sensor_{nullptr};
  sensor::Sensor *respiration_rate_sensor_{nullptr};
  sensor::Sensor *heart_rate_sensor_{nullptr};

  DFRobot_HumanDetection hu_;  // Library instance
};

}  // namespace esphome
