#pragma once

#include "esphome/components/sensor/sensor.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/number/number.h"
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "DFRobot_HumanDetection.h"

namespace esphome {
namespace dfrobot_c1001 {

class DFRobotC1001Component : public PollingComponent, public uart::UARTDevice {
 public:
  DFRobotC1001Component() : PollingComponent(1000) {}

  void setup() override;
  void update() override;
  void dump_config() override;

  void set_presence_sensor(sensor::Sensor *presence_sensor) { presence_sensor_ = presence_sensor; }
  void set_movement_sensor(sensor::Sensor *movement_sensor) { movement_sensor_ = movement_sensor; }
  void set_moving_range_sensor(sensor::Sensor *moving_range_sensor) { moving_range_sensor_ = moving_range_sensor; }
  void set_breathe_value_sensor(sensor::Sensor *breathe_value_sensor) { breathe_value_sensor_ = breathe_value_sensor; }
  void set_heart_rate_sensor(sensor::Sensor *heart_rate_sensor) { heart_rate_sensor_ = heart_rate_sensor; }
  void set_height_number(number::Number *height_number) { height_number_ = height_number; }
  void set_work_mode_switch(switch_::Switch *work_mode_switch) { work_mode_switch_ = work_mode_switch; }

 protected:
  sensor::Sensor *presence_sensor_{nullptr};
  sensor::Sensor *movement_sensor_{nullptr};
  sensor::Sensor *moving_range_sensor_{nullptr};
  sensor::Sensor *breathe_value_sensor_{nullptr};
  sensor::Sensor *heart_rate_sensor_{nullptr};
  number::Number *height_number_{nullptr};
  switch_::Switch *work_mode_switch_{nullptr};

 private:
  DFRobot_HumanDetection *hu;
};

}  // namespace dfrobot_c1001
}  // namespace esphome