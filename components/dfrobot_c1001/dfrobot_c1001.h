
#pragma once
#include "esphome.h"
#include "DFRobot_HumanDetection.h"

namespace esphome {
namespace dfrobot_c1001 {

class DFRobotC1001Component : public PollingComponent, public uart::UARTDevice {
 public:
  DFRobotC1001Component() : PollingComponent(1500) {}

  void setup() override;
  void update() override;

  // Setters for ESPHome entities
  void set_presence_sensor(sensor::Sensor *presence_sensor) { this->presence_sensor_ = presence_sensor; }
  void set_motion_sensor(sensor::Sensor *motion_sensor) { this->motion_sensor_ = motion_sensor; }
  void set_distance_sensor(sensor::Sensor *distance_sensor) { this->distance_sensor_ = distance_sensor; }
  void set_energy_sensor(sensor::Sensor *energy_sensor) { this->energy_sensor_ = energy_sensor; }
  void set_installation_height_number(number::Number *installation_height) { this->installation_height_number_ = installation_height; }
  void set_fall_detection_switch(switch_::Switch *fall_detection_switch) { this->fall_detection_switch_ = fall_detection_switch; }
  void set_sleep_mode_select(select::Select *sleep_mode_select) { this->sleep_mode_select_ = sleep_mode_select; }

 protected:
  DFRobot_HumanDetection *sensor_{nullptr};
  
  // Sensors
  sensor::Sensor *presence_sensor_{nullptr};
  sensor::Sensor *motion_sensor_{nullptr};
  sensor::Sensor *distance_sensor_{nullptr};
  sensor::Sensor *energy_sensor_{nullptr};

  // Numbers
  number::Number *installation_height_number_{nullptr};

  // Switches
  switch_::Switch *fall_detection_switch_{nullptr};

  // Selectors
  select::Select *sleep_mode_select_{nullptr};
};

}  // namespace dfrobot_c1001
}  // namespace esphome
