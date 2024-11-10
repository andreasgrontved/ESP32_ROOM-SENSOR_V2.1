#pragma once

#include <memory>
#include <string>

namespace esphome {
namespace dfrobot_c1001 {

class DFRobotC1001Component;  // Forward declaration

// Base Command class
class Command {
 public:
  virtual ~Command() = default;
  virtual uint8_t execute(DFRobotC1001Component *parent) = 0;  // Executes the command
};

// Reset Command class
class ResetCommand : public Command {
 public:
  uint8_t execute(DFRobotC1001Component *parent) override;
};

// Set Height Command class
class SetHeightCommand : public Command {
 public:
  explicit SetHeightCommand(uint16_t height) : height_(height) {}
  uint8_t execute(DFRobotC1001Component *parent) override;

 private:
  uint16_t height_;
};

// Set Sensitivity Command class
class SetSensitivityCommand : public Command {
 public:
  explicit SetSensitivityCommand(uint8_t sensitivity) : sensitivity_(sensitivity) {}
  uint8_t execute(DFRobotC1001Component *parent) override;

 private:
  uint8_t sensitivity_;
};

// Set Fall Time Command class
class SetFallTimeCommand : public Command {
 public:
  explicit SetFallTimeCommand(uint16_t fall_time) : fall_time_(fall_time) {}
  uint8_t execute(DFRobotC1001Component *parent) override;

 private:
  uint16_t fall_time_;
};

}  // namespace dfrobot_c1001
}  // namespace esphome
