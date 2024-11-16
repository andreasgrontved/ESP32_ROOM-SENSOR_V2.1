#include "dfrobot_c1001.h"

namespace esphome {
namespace dfrobot_c1001 {

void DFRobotC1001::setup() {
  ESP_LOGCONFIG(TAG, "Setting up DFRobot C1001...");

  if (hu.begin() != 0) {
    ESP_LOGE(TAG, "Sensor initialization failed!");
    mark_failed();
    return;
  }

  if (hu.configWorkMode(hu.eSleepMode) != 0) {
    ESP_LOGE(TAG, "Failed to configure work mode");
    mark_failed();
    return;
  }

  hu.configLEDLight(hu.eHPLed, 1);  // Enable HP LED for testing
  ESP_LOGD(TAG, "Initialization successful");
}

void DFRobotC1001::update() {
  if (this->presence_sensor_ != nullptr) {
    this->presence_sensor_->publish_state(hu.smHumanData(hu.eHumanPresence));
  }
  if (this->distance_sensor_ != nullptr) {
    this->distance_sensor_->publish_state(hu.getBreatheValue());  // Replace with actual distance metric
  }
  ESP_LOGD(TAG, "Sensor data updated");
}

}  // namespace dfrobot_c1001
}  // namespace esphome
