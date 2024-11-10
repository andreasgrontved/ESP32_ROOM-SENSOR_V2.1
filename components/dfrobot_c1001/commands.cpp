#include "commands.h"
#include "dfrobot_c1001.h"
#include "esphome/core/log.h"

namespace esphome {
namespace dfrobot_c1001 {

static const char *TAG = "dfrobot_c1001.command";

uint8_t ResetCommand::execute(DFRobotC1001Component *parent) {
  ESP_LOGI(TAG, "Executing Reset Command");
  parent->set_presence_(false);
  return 1;  // Command complete
}

uint8_t SetHeightCommand::execute(DFRobotC1001Component *parent) {
  ESP_LOGI(TAG, "Executing Set Height Command");
  parent->set_installation_height(height_);
  return 1;
}

uint8_t SetSensitivityCommand::execute(DFRobotC1001Component *parent) {
  ESP_LOGI(TAG, "Executing Set Sensitivity Command");
  parent->set_sensitivity(sensitivity_);
  return 1;
}

uint8_t SetFallTimeCommand::execute(DFRobotC1001Component *parent) {
  ESP_LOGI(TAG, "Executing Set Fall Time Command");
  parent->set_fall_time(fall_time_);
  return 1;
}

}  // namespace dfrobot_c1001
}  // namespace esphome
