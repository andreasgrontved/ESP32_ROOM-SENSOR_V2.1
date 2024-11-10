#pragma once

#include "dfrobot_c1001.h"
#include <string>

namespace esphome {
namespace dfrobot_c1001 {

class DFRobotC1001Component;

// Base Command class
class Command {
 public:
  virtual ~Command() = default;
  virtual uint8_t execute(DFRobotC1001Component *parent) = 0;
};

class ResetCommand : public Command {
 public:
  uint8_t execute(DFRobotC1001Component *parent) override {
    parent->set_presence_(false);  // Example action for reset
    return 1;  // Command complete
  }
};

}  // namespace dfrobot_c1001
}  // namespace esphome
