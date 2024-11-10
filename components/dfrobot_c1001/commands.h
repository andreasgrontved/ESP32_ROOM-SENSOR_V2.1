#pragma once

#include <cstdint>
#include <string>
#include "esphome/core/helpers.h"
#include "DFRobot_HumanDetection.h"

namespace esphome {
namespace dfrobot_c1001 {

class DFRobotC1001Component;

class Command {
 public:
  virtual ~Command() = default;
  virtual uint8_t execute(DFRobotC1001Component *parent);
  virtual uint8_t on_message(std::string &message) = 0;

 protected:
  DFRobotC1001Component *parent_{nullptr};
  std::string cmd_;
  bool cmd_sent_{false};
  int8_t retries_left_{2};
  uint32_t cmd_duration_ms_{1000};
  uint32_t timeout_ms_{1500};
};

class ReadStateCommand : public Command {
 public:
  uint8_t execute(DFRobotC1001Component *parent) override;
  uint8_t on_message(std::string &message) override;

 protected:
  uint32_t timeout_ms_{500};
};

class PowerCommand : public Command {
 public:
  PowerCommand(bool power_on) : power_on_(power_on) {
    cmd_ = power_on ? "sensorStart" : "sensorStop";
  };
  uint8_t on_message(std::string &message) override;

 protected:
  bool power_on_;
};

class SetWorkModeCommand : public Command {
 public:
  SetWorkModeCommand(DFRobot_HumanDetection::eWorkMode mode) : mode_(mode) {
    cmd_ = mode == DFRobot_HumanDetection::eFallingMode ? "setWorkMode 1" : "setWorkMode 2";
  }
  uint8_t on_message(std::string &message) override;

 protected:
  DFRobot_HumanDetection::eWorkMode mode_;
};

class SetInstallationHeightCommand : public Command {
 public:
  SetInstallationHeightCommand(uint16_t height) {
    char tmp_cmd[20] = {0};
    sprintf(tmp_cmd, "setInstallHeight %d", height);
    cmd_ = std::string(tmp_cmd);
  }
  uint8_t on_message(std::string &message) override;
};

class SetFallSensitivityCommand : public Command {
 public:
  SetFallSensitivityCommand(uint8_t sensitivity) : sensitivity_(sensitivity) {
    if (sensitivity > 3) sensitivity_ = 3;
    char tmp_cmd[20] = {0};
    sprintf(tmp_cmd, "setFallSensitivity %d", sensitivity);
    cmd_ = std::string(tmp_cmd);
  };
  uint8_t on_message(std::string &message) override;

 protected:
  uint8_t sensitivity_;
};

class LedModeCommand : public Command {
 public:
  LedModeCommand(bool active) : active_(active) {
    cmd_ = active ? "setLedMode 1" : "setLedMode 0";
  };
  uint8_t on_message(std::string &message) override;

 protected:
  bool active_;
};

class ResetSystemCommand : public Command {
 public:
  ResetSystemCommand() { cmd_ = "resetSystem"; }
  uint8_t on_message(std::string &message) override;
};

class SaveConfigurationCommand : public Command {
 public:
  SaveConfigurationCommand() { cmd_ = "saveConfig"; }
  uint8_t on_message(std::string &message) override;

 protected:
  uint32_t cmd_duration_ms_{3000};
  uint32_t timeout_ms_{3500};
};

}  // namespace dfrobot_c1001
}  // namespace esphome
