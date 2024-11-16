#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "DFRobot_HumanDetection.h"

namespace esphome {
namespace dfrobot_c1001 {

class DFRobotC1001 : public PollingComponent, public uart::UARTDevice {
 public:
  // Constructor
  DFRobotC1001() = default;

  // Setup and update methods
  void setup() override;
  void update() override;

  // Setters for sensors
  void set_presence_sensor(sensor::Sensor *presence_sensor) { presence_sensor_ = presence_sensor; }
  void set_distance_sensor(sensor::Sensor *distance_sensor) { distance_sensor_ = distance_sensor; }

 private:
  // Pointer to DFRobot's human detection library
  DFRobot_HumanDetection hu;

  // Sensor pointers for presence and distance
  sensor::Sensor *presence_sensor_{nullptr};
  sensor::Sensor *distance_sensor_{nullptr};
};

}  // namespace dfrobot_c1001
}  // namespace esphome
