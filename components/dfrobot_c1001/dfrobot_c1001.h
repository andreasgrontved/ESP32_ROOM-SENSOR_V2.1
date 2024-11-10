#pragma once

#include "esphome/components/uart/uart.h"
#include "esphome/core/component.h"
#include <memory>
#include <string>
#include <queue>

namespace esphome {
namespace dfrobot_c1001 {

class Command;  // Forward declaration for the Command class

class DFRobotC1001Component : public uart::UARTDevice, public Component {
 public:
  void setup() override;
  void loop() override;

  // Configuration methods
  void set_installation_height(uint16_t height);
  void set_sensitivity(uint8_t sensitivity);
  void set_fall_time(uint16_t time);
  void factory_reset();

  // Command handling methods
  uint8_t read_message_();                      // Reads messages from the UART
  bool send_cmd_(const char *cmd, uint32_t duration);  // Sends command via UART
  void set_presence_(bool presence);            // Updates presence state

 protected:
  uint32_t ts_last_cmd_sent_{0};                // Timestamp for command timing
  char read_buffer_[255];                       // Buffer for storing received messages

  // Command queue for processing commands in sequence
  std::queue<std::unique_ptr<Command>> command_queue_;
};

// Define a base Command class for processing individual commands
class Command {
 public:
  virtual ~Command() = default;
  virtual uint8_t execute(DFRobotC1001Component *parent) = 0;  // Executes the command logic
};

}  // namespace dfrobot_c1001
}  // namespace esphome
