#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "DFRobot_HumanDetection.h"

namespace esphome {
namespace dfrobot_c1001 {

class DFRobotC1001 : public uart::UARTDevice, public PollingComponent {
 public:
  DFRobotC1001() : PollingComponent(1000) {}  // Adjust interval as needed

  void setup() override;
  void update() override;  // Replaces loop()
  void dump_config() override;

  // Sensor objects for each data point
  sensor::Sensor *presence_sensor_{nullptr};
  sensor::Sensor *movement_sensor_{nullptr};
  sensor::Sensor *movement_param_sensor_{nullptr};
  sensor::Sensor *respiration_rate_sensor_{nullptr};
  sensor::Sensor *heart_rate_sensor_{nullptr};

  void set_presence_sensor(sensor::Sensor *sensor) { presence_sensor_ = sensor; }
  void set_movement_sensor(sensor::Sensor *sensor) { movement_sensor_ = sensor; }
  void set_movement_param_sensor(sensor::Sensor *sensor) { movement_param_sensor_ = sensor; }
  void set_respiration_rate_sensor(sensor::Sensor *sensor) { respiration_rate_sensor_ = sensor; }
  void set_heart_rate_sensor(sensor::Sensor *sensor) { heart_rate_sensor_ = sensor; }

 protected:
  DFRobot_HumanDetection hu;
};

}  // namespace dfrobot_c1001
}  // namespace esphome
