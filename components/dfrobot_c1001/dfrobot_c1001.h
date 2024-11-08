#pragma once

#include "esphome.h"

namespace esphome {
namespace dfrobot_c1001 {

class DFRobotC1001Sensor : public sensor::Sensor, public PollingComponent, public uart::UARTDevice {
 public:
  void setup() override;
  void update() override;
  void dump_config() override;
};

}  // namespace dfrobot_c1001
}  // namespace esphome
