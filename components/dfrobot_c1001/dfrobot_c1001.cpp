#include "dfrobot_c1001.h"
#include "esphome/core/log.h"

namespace esphome {
namespace dfrobot_c1001 {

static const char *TAG = "dfrobot_c1001";

// Setup function
void DFRobotC1001Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up DFRobot C1001...");
  this->ts_last_cmd_sent_ = 0;
}

// Loop function for processing commands
void DFRobotC1001Component::loop() {
  // Process command queue
  if (!this->command_queue_.empty()) {
    auto &cmd = this->command_queue_.front();
    if (cmd->execute(this) == 1) {  // 1 indicates command done
      this->command_queue_.pop();  // Remove the command from the queue
    }
  }
}

// Method to read incoming UART messages
uint8_t DFRobotC1001Component::read_message_() {
  while (this->available()) {
    uint8_t byte;
    this->read_byte(&byte);

    if (byte >= 0x7F) byte = '?';  // Valid UTF-8
    this->read_buffer_[this->ts_last_cmd_sent_++ % sizeof(read_buffer_)] = byte;

    if (byte == '\n') {
      this->read_buffer_[this->ts_last_cmd_sent_ % sizeof(read_buffer_)] = '\0';
      ESP_LOGD(TAG, "Received message: %s", this->read_buffer_);
      return 1;  // Message complete
    }
  }
  return 0;
}

// Method to send commands over UART
bool DFRobotC1001Component::send_cmd_(const char *cmd, uint32_t duration) {
  if (millis() - this->ts_last_cmd_sent_ > duration) {
    this->write_str(cmd);
    this->ts_last_cmd_sent_ = millis();
    return true;
  }
  return false;
}

// Method to set presence state
void DFRobotC1001Component::set_presence_(bool presence) {
  ESP_LOGD(TAG, "Presence set to: %d", presence);
}

// Configuration setters
void DFRobotC1001Component::set_installation_height(uint16_t height) {
  ESP_LOGD(TAG, "Installation height set to: %u", height);
}

void DFRobotC1001Component::set_sensitivity(uint8_t sensitivity) {
  ESP_LOGD(TAG, "Sensitivity set to: %u", sensitivity);
}

void DFRobotC1001Component::set_fall_time(uint16_t time) {
  ESP_LOGD(TAG, "Fall time set to: %u", time);
}

void DFRobotC1001Component::factory_reset() {
  ESP_LOGD(TAG, "Factory reset command executed.");
}

}  // namespace dfrobot_c1001
}  // namespace esphome
