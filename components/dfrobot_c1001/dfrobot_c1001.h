#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "DFRobot_HumanDetection.h"

namespace esphome {
namespace dfrobot_c1001 {

class DFRobotC1001 : public uart::UARTDevice, public PollingComponent {
 public:
  DFRobotC1001() : PollingComponent(1000) {}  // Adjust update interval as needed

  void setup() override;
  void update() override;
  void dump_config() override;

  // Sub-sensors for each data point
  sensor::Sensor *presence_sensor{nullptr};
  sensor::Sensor *movement_sensor{nullptr};
  sensor::Sensor *movement_param_sensor{nullptr};
  sensor::Sensor *respiration_rate_sensor{nullptr};
  sensor::Sensor *heart_rate_sensor{nullptr};

  // Setters for each sensor
  void set_presence_sensor(sensor::Sensor *sensor) { presence_sensor = sensor; }
  void set_movement_sensor(sensor::Sensor *sensor) { movement_sensor = sensor; }
  void set_movement_param_sensor(sensor::Sensor *sensor) { movement_param_sensor = sensor; }
  void set_respiration_rate_sensor(sensor::Sensor *sensor) { respiration_rate_sensor = sensor; }
  void set_heart_rate_sensor(sensor::Sensor *sensor) { heart_rate_sensor = sensor; }

 protected:
  DFRobot_HumanDetection hu;
};

}  // namespace dfrobot_c1001
}  // namespace esphome
