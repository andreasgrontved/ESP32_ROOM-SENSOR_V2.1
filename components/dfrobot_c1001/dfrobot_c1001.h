#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "DFRobot_HumanDetection.h"  // Include your sensor library

namespace esphome {
namespace dfrobot_c1001 {

class DFRobotC1001 : public uart::UARTDevice, public Component {
  public:
    // Constructor
    DFRobotC1001(uart::UARTComponent *parent);
    
    void setup() override;
    void loop() override;
    void dump_config() override;

    // Sensors to expose
    Sensor *presence_sensor = new Sensor();
    Sensor *motion_sensor = new Sensor();
    Sensor *movement_param_sensor = new Sensor();
    Sensor *respiration_rate_sensor = new Sensor();
    Sensor *heart_rate_sensor = new Sensor();

  private:
    // Instance of your sensor class
    DFRobot_HumanDetection hu_;
};

}  // namespace dfrobot_c1001
}  // namespace esphome