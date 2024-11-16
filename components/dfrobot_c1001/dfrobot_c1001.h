#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "DFRobot_HumanDetection.h"  // Include the DFRobot library

namespace esphome {
namespace dfrobot_c1001 {

class DFRobotC1001 : public uart::UARTDevice, public Component {
 public:
  explicit DFRobotC1001(Stream *stream);
  void setup() override;
  void loop() override;
  void dump_config() override;

 private:
  DFRobot_HumanDetection sensor_;  // Instance of the DFRobot library
  void process_sensor_data();      // Method to process data from the sensor
};

}  // namespace dfrobot_c1001
}  // namespace esphome
