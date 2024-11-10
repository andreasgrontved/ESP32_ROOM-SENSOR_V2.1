#pragma once

#include "esphome/components/uart/uart.h"
#include "esphome/core/component.h"
#include <memory>
#include <string>
#include <queue>

namespace esphome {
namespace dfrobot_c1001 {

class Command;  // Forward declaration for Command

class DFRobotC1001Component : public uart::UARTDevice, public Component {
 public:
  void setup() override;
  void loop() override;

  void set_installation_height(uint16_t height);
  void set_sensitivity(uint8_t sensitivity);
  void set_fall_time(uint16_t time);
  void factory_reset();

  uint8_t read_message_();  // New method to handle reading messages
  bool send_cmd_(const char *cmd, uint32_t duration);  // New method to send commands
  void set_presence_(bool presence);  // New method for setting presence

 protected:
  uint32_t ts_last_cmd_sent_{0};  // Command timing variable
  char read_buffer_[255];  // Buffer to store messages

  // Queue for handling commands in a circular buffer style
  std::queue<std::unique_ptr<Command>> command_queue_;
};

// Define a basic Command class for handling individual commands
class Command {
 public:
  virtual ~Command() = default;
  virtual uint8_t execute(DFRobotC1001Component *parent) = 0;  // Execute command logic
};

}  // namespace dfrobot_c1001
}  // namespace esphome
