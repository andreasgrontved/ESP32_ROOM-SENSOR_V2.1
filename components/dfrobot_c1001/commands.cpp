#include "commands.h"
#include "esphome/core/log.h"

namespace esphome {
namespace dfrobot_c1001 {

static const char *TAG = "dfrobot_c1001.commands";

// Execute method for ResetCommand example
uint8_t ResetCommand::execute(DFRobotC1001Component *parent) {
  ESP_LOGD(TAG, "Executing ResetCommand...");
  parent->set_presence_(false);
  return 1;  // Command done
}

}  // namespace dfrobot_c1001
}  // namespace esphome
