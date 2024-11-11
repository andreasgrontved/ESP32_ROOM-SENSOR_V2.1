#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

#include "DFRobot_HumanDetection.h"

namespace esphome {
namespace dfrobot_c1001 {

class DFRobotC1001 : public uart::UARTDevice, public Component {
 public:
  DFRobotC1001(uart::UARTComponent *parent);

  void setup() override;
  void loop() override;
  void dump_config() override;

  // Sensors to expose
  esphome::binary_sensor::BinarySensor *presence_binary_sensor = new esphome::binary_sensor::BinarySensor();
  esphome::sensor::Sensor *motion_sensor = new esphome::sensor::Sensor();
  esphome::sensor::Sensor *movement_param_sensor = new esphome::sensor::Sensor();
  esphome::sensor::Sensor *respiration_rate_sensor = new esphome::sensor::Sensor();
  esphome::sensor::Sensor *heart_rate_sensor = new esphome::sensor::Sensor();

 private:
  DFRobot_HumanDetection hu_;
};

}  // namespace dfrobot_c1001
}  // namespace esphome
