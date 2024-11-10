#pragma once

#include "esphome/components/uart/uart.h"
#include "esphome/core/automation.h"
#include "esphome/core/component.h"
#include "DFRobot_HumanDetection.h"  // DFRobot library

#ifdef USE_BINARY_SENSOR
#include "esphome/components/binary_sensor/binary_sensor.h"
#endif
#ifdef USE_SWITCH
#include "esphome/components/switch/switch.h"
#endif

namespace esphome {
namespace dfrobot_c1001 {

const uint8_t MMWAVE_READ_BUFFER_LENGTH = 255;

class DFRobotC1001Component : public uart::UARTDevice, public Component {
#ifdef USE_SWITCH
  SUB_SWITCH(sensor_active)
  SUB_SWITCH(turn_on_led)
  SUB_SWITCH(fall_detection)
#endif

 public:
  void dump_config() override;
  void loop() override;
  void set_active(bool active) {
    if (active != active_) {
#ifdef USE_SWITCH
      if (this->sensor_active_switch_ != nullptr)
        this->sensor_active_switch_->publish_state(active);
#endif
      active_ = active;
    }
  }
  bool is_active() { return active_; }

  void set_led_active(bool active) {
    if (led_active_ != active) {
#ifdef USE_SWITCH
      if (this->turn_on_led_switch_ != nullptr)
        this->turn_on_led_switch_->publish_state(active);
#endif
      led_active_ = active;
    }
  }
  bool is_led_active() { return led_active_; }

  void set_fall_detection(bool enabled) {
#ifdef USE_SWITCH
    if (this->fall_detection_switch_ != nullptr)
      this->fall_detection_switch_->publish_state(enabled);
#endif
    fall_detection_enabled_ = enabled;
  }
  bool is_fall_detection_enabled() { return fall_detection_enabled_; }

  void set_installation_height(uint16_t height) { installation_height_ = height; }
  uint16_t get_installation_height() { return installation_height_; }

  void set_fall_sensitivity(uint8_t sensitivity) { fall_sensitivity_ = sensitivity; }
  uint8_t get_fall_sensitivity() { return fall_sensitivity_; }

#ifdef USE_BINARY_SENSOR
  void set_presence_binary_sensor(binary_sensor::BinarySensor *presence_binary_sensor) {
    presence_binary_sensor_ = presence_binary_sensor;
  }
#endif

 protected:
#ifdef USE_BINARY_SENSOR
  binary_sensor::BinarySensor *presence_binary_sensor_{nullptr};
#endif

  bool active_{false};
  bool led_active_{false};
  bool fall_detection_enabled_{false};
  uint16_t installation_height_{270};  // Default height in cm
  uint8_t fall_sensitivity_{3};        // Default fall sensitivity (0-3)
  char read_buffer_[MMWAVE_READ_BUFFER_LENGTH];
  size_t read_pos_{0};

  void process_data_();
  void set_presence_(bool presence);

  DFRobot_HumanDetection hu_;  // Sensor instance
};

}  // namespace dfrobot_c1001
}  // namespace esphome
