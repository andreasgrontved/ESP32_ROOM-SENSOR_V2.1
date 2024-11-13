#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"


namespace esphome {
namespace dfrobot_c1001 {

class dfrobot_c1001 : public uart::UARTDevice, public Component {
  public:
    void setup() override;
    void loop() override;
    void dump_config() override;
};


}  // namespace dfrobot_c1001
}  // namespace esphome