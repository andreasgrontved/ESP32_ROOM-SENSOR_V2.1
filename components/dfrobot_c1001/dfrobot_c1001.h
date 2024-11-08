#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"
#include "DFRobot_HumanDetection.h"


namespace esphome {
namespace dfrobot_c1001 {

class dfrobot_c1001 : public sensor::Sensor, public PollingComponent, public uart::UARTDevice {
 public:
  void setup() override;
  void update() override;
  void loop() override;
  void dump_config() override;
};

}  // namespace dfrobot_c1001
}  // namespace esphome
