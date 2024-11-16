#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace dfrobot_c1001 {

class DFRobotC1001 : public uart::UARTDevice, public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;

  // Custom methods to handle sensor functionality
  void process_sensor_data();
};

}  // namespace dfrobot_c1001
}  // namespace esphome
