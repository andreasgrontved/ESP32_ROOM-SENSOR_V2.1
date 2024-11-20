
#include "dfrobot_c1001.h"

namespace esphome {
namespace dfrobot_c1001 {

void DFRobotC1001Component::setup() {
  this->sensor_ = new DFRobot_HumanDetection(&Serial1);
  if (!this->sensor_->begin()) {
    ESP_LOGE("DFRobot_C1001", "Sensor initialization failed!");
  }
}

void DFRobotC1001Component::update() {
  if (this->sensor_ != nullptr) {
    uint16_t presence = this->sensor_->smHumanData(DFRobot_HumanDetection::eHumanPresence);
    uint16_t motion = this->sensor_->smHumanData(DFRobot_HumanDetection::eHumanMovement);
    uint16_t distance = this->sensor_->smHumanData(DFRobot_HumanDetection::eHumanDistance);
    uint16_t energy = this->sensor_->smHumanData(DFRobot_HumanDetection::eHumanMovingRange);

    if (this->presence_sensor_ != nullptr)
      this->presence_sensor_->publish_state(presence);
    if (this->motion_sensor_ != nullptr)
      this->motion_sensor_->publish_state(motion);
    if (this->distance_sensor_ != nullptr)
      this->distance_sensor_->publish_state(distance);
    if (this->energy_sensor_ != nullptr)
      this->energy_sensor_->publish_state(energy);

    // Installation height (if configured)
    if (this->installation_height_number_ != nullptr) {
      uint16_t height = this->sensor_->dmGetInstallHeight();
      this->installation_height_number_->publish_state(height);
    }

    // Fall detection switch state (if configured)
    if (this->fall_detection_switch_ != nullptr) {
      bool fall_state = this->sensor_->getFallData(DFRobot_HumanDetection::eFallState);
      this->fall_detection_switch_->publish_state(fall_state);
    }

    // Sleep mode selector state (if configured)
    if (this->sleep_mode_select_ != nullptr) {
      uint8_t mode = this->sensor_->getWorkMode();
      this->sleep_mode_select_->publish_state(mode == DFRobot_HumanDetection::eSleepMode ? "Sleep" : "Falling");
    }
  }
}

}  // namespace dfrobot_c1001
}  // namespace esphome
