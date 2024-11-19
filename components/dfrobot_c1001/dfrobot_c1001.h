#pragma once

#include "esphome.h"
#include "DFRobot_HumanDetection.h"

namespace esphome {
class DFRobotC1001 : public PollingComponent {
 public:
  explicit DFRobotC1001(UARTComponent *uart);
  void setup() override;
  void update() override;

  Sensor *presence_sensor = new Sensor();
  Sensor *motion_sensor = new Sensor();
  Sensor *movement_param_sensor = new Sensor();
  Sensor *respiration_rate_sensor = new Sensor();
  Sensor *heart_rate_sensor = new Sensor();

 private:
  DFRobot_HumanDetection hu_;
};
}  // namespace esphome
