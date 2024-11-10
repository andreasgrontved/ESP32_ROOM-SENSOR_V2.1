#pragma once

#include "esphome/components/switch/switch.h"
#include "esphome/core/component.h"
#include "../dfrobot_c1001.h"

namespace esphome {
namespace dfrobot_c1001 {

class DFRobotC1001Switch : public switch_::Switch, public Component, public Parented<DFRobotC1001Component> {};

class C1001PowerSwitch : public DFRobotC1001Switch {
 public:
  void write_state(bool state) override;
};

class C1001LedSwitch : public DFRobotC1001Switch {
 public:
  void write_state(bool state) override;
};

class C1001UartPresenceSwitch : public DFRobotC1001Switch {
 public:
  void write_state(bool state) override;
};

class C1001StartAfterBootSwitch : public DFRobotC1001Switch {
 public:
  void write_state(bool state) override;
};

}  // namespace dfrobot_c1001
}  // namespace esphome
