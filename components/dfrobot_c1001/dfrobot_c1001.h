#pragma once

#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"
#include "DFRobot_HumanDetection.h"

namespace esphome {
namespace dfrobot_c1001 {

class DFRobotC1001Component : public PollingComponent {
 public:
  DFRobotC1001Component() : PollingComponent(1000) {}

  void setup() override;
  void update() override;
  void dump_config() override;

  Sensor *presence_sensor = new Sensor();
  Sensor *movement_sensor = new Sensor();
  Sensor *moving_range_sensor = new Sensor();
  Sensor *breathe_value_sensor = new Sensor();
  Sensor *heart_rate_sensor = new Sensor();

 private:
  DFRobot_HumanDetection *hu;
};

}  // namespace dfrobot_c1001
}  // namespace esphome