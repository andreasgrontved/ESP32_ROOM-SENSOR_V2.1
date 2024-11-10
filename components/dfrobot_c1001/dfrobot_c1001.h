#pragma once

#include "esphome/components/uart/uart.h"
#include "esphome/core/component.h"
#include "commands.h"
#include <queue>
#include <memory>

namespace esphome {
namespace dfrobot_c1001 {

class DFRobotC1001Component : public uart::UARTDevice, public Component {
 public:
  void setup() override;
  void loop() override;

  void set_installation_height(uint16_t height);
  void set_sensitivity(uint8_t sensitivity);
  void set_fall_time(uint16_t time);
  void factory_reset();

  uint8_t read_message_();
  bool send_cmd_(const char *cmd, uint32_t duration);
  void set_presence_(bool presence);

  void enqueue_command(std::unique_ptr<Command> cmd);

 protected:
  std::queue<std::unique_ptr<Command>> command_queue_;  // Queue for commands
  uint32_t ts_last_cmd_sent_{0};                        // Command timestamp
  char read_buffer_[255];                               // Buffer for messages

  void process_command_();                              // Processes the command queue
};

}  // namespace dfrobot_c1001
}  // namespace esphome
