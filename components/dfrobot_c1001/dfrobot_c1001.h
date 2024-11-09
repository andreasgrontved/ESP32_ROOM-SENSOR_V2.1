#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "DFRobot_HumanDetection.h"

namespace esphome {
namespace dfrobot_c1001 {

class dfrobot_c1001 : public uart::UARTDevice, public Component {
 public:
    // Constructor, initializes UART device with the parent component
    DFRobotC1001Component(uart::UARTComponent *parent) : uart::UARTDevice(parent), hu(&Serial1) {}

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

 private:
    DFRobot_HumanDetection hu;

    // Default configuration values
    bool led_enabled_{true};           // LED initially enabled
    int fall_sensitivity_{3};          // Default fall sensitivity (range: 0-3)
    int installation_height_{270};     // Default installation height in cm
};

}  // namespace dfrobot_c1001
}  // namespace esphome
