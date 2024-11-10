#include "dfrobot_c1001.h"
#include "commands.h"
#include "esphome/core/log.h"

namespace esphome {
namespace dfrobot_c1001 {

static const char *TAG = "dfrobot_c1001";

void DFRobotC1001Component::setup() {
  // Setup component here
}

void DFRobotC1001Component::loop() {
  if (!command_queue_.empty()) {
    process_command_();  // Process the next command
  }
}

void DFRobotC1001Component::set_installation_height(uint16_t height) {
  ESP_LOGI(TAG, "Setting height to %d", height);
  // Set height logic here
}

void DFRobotC1001Component::set_sensitivity(uint8_t sensitivity) {
  ESP_LOGI(TAG, "Setting sensitivity to %d", sensitivity);
  // Set sensitivity logic here
}

void DFRobotC1001Component::set_fall_time(uint16_t time) {
  ESP_LOGI(TAG, "Setting fall time to %d", time);
  // Set fall time logic here
}

void DFRobotC1001Component::factory_reset() {
  ESP_LOGI(TAG, "Performing factory reset");
  // Factory reset logic here
}

void DFRobotC1001Component::enqueue_command(std::unique_ptr<Command> cmd) {
  command_queue_.push(std::move(cmd));
}

void DFRobotC1001Component::process_command_() {
  if (!command_queue_.empty()) {
    auto &cmd = command_queue_.front();
    if (cmd->execute(this)) {
      command_queue_.pop();  // Remove command after execution
    }
  }
}

}  // namespace dfrobot_c1001
}  // namespace esphome
