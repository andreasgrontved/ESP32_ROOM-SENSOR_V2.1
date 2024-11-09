#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "DFRobot_HumanDetection.h"

namespace esphome {
namespace dfrobot_c1001 {

class DFRobotC1001Component : public Component, public uart::UARTDevice {
 public:
  DFRobotC1001Component(uart::UARTComponent *parent);

    // Standard ESPHome methods
    void setup() override;
    void loop() override;
    void dump_config() override;

    // Configuration methods
    void set_led_enabled(bool enabled);
    void set_fall_sensitivity(int sensitivity);
    void set_installation_height(int height_cm);

    // Sensor data retrieval methods
    int get_presence_status();
    int get_motion_status();
    int get_fall_status();
    int get_residency_status();

 protected:
  DFRobot_HumanDetection hu;

    // Default configuration values
    bool led_enabled_{false};           // LED initially enabled
    int fall_sensitivity_{0};          // Default fall sensitivity (range: 0-3)
    int installation_height_{200};     // Default installation height in cm
};

}  // namespace dfrobot_c1001
}  // namespace esphome
