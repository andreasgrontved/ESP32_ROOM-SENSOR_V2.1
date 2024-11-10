#pragma once

#include "dfrobot_c1001.h"
#include <string>

namespace esphome {
namespace dfrobot_c1001 {

class DFRobotC1001Component;  // Forward declaration of the component class

// Base Command class
class Command {
 public:
  virtual ~Command() = default;
  virtual uint8_t execute(DFRobotC1001Component *parent) = 0;  // Pure virtual function
};

// Reset Command class
class ResetCommand : public Command {
 public:
  uint8_t execute(DFRobotC1001Component *parent) override {
    parent->set_presence_(false);  // Example action for reset
    return 1;  // Command complete
  }
};

// Set Installation Height Command class
class SetHeightCommand : public Command {
 public:
  explicit SetHeightCommand(uint16_t height) : height_(height) {}
  uint8_t execute(DFRobotC1001Component *parent) override {
    parent->set_installation_height(height_);
    return 1;  // Command complete
  }

 private:
  uint16_t height_;
};

// Set Sensitivity Command class
class SetSensitivityCommand : public Command {
 public:
  explicit SetSensitivityCommand(uint8_t sensitivity) : sensitivity_(sensitivity) {}
  uint8_t execute(DFRobotC1001Component *parent) override {
    parent->set_sensitivity(sensitivity_);
    return 1;  // Command complete
  }

 private:
  uint8_t sensitivity_;
};

// Set Fall Time Command class
class SetFallTimeCommand : public Command {
 public:
  explicit SetFallTimeCommand(uint16_t fall_time) : fall_time_(fall_time) {}
  uint8_t execute(DFRobotC1001Component *parent) override {
    parent->set_fall_time(fall_time_);
    return 1;  // Command complete
  }

 private:
  uint16_t fall_time_;
};

}  // namespace dfrobot_c1001
}  // namespace esphome
