#include "dfrobot_c1001.h"
#include "esphome/core/log.h"

namespace esphome {
namespace dfrobot_c1001 {

static const char *const TAG = "dfrobot_c1001";

void DFRobotC1001Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up DFRobot C1001...");
  this->human_detection = new DFRobot_HumanDetection(&Serial1);

  if (this->human_detection->begin() == 0) {
    ESP_LOGI(TAG, "DFRobot C1001 initialized successfully.");
  } else {
    ESP_LOGE(TAG, "Failed to initialize DFRobot C1001.");
  }
}

void DFRobotC1001Component::update() {
  if (this->presence_sensor_ != nullptr) {
    int presence = this->human_detection->smHumanData(DFRobot_HumanDetection::eHumanPresence);
    this->presence_sensor_->publish_state(presence);
  }
  if (this->movement_sensor_ != nullptr) {
    int movement = this->human_detection->smHumanData(DFRobot_HumanDetection::eHumanMovement);
    this->movement_sensor_->publish_state(movement);
  }
  if (this->moving_range_sensor_ != nullptr) {
    int moving_range = this->human_detection->smHumanData(DFRobot_HumanDetection::eHumanMovingRange);
    this->moving_range_sensor_->publish_state(moving_range);
  }
}

void DFRobotC1001Component::dump_config() {
  ESP_LOGCONFIG(TAG, "DFRobot C1001:");
  LOG_SENSOR("  ", "Presence", this->presence_sensor_);
  LOG_SENSOR("  ", "Movement", this->movement_sensor_);
  LOG_SENSOR("  ", "Moving Range", this->moving_range_sensor_);
}

}  // namespace dfrobot_c1001
}  // namespace esphome
