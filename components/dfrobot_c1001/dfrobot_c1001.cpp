#include "esphome/core/log.h"
#include "dfrobot_c1001.h"

namespace esphome {
namespace dfrobot_c1001 {

static const char *TAG = "dfrobot_c1001";

DFRobotC1001::DFRobotC1001(HardwareSerial *serial) : sensor_(serial) {}

void DFRobotC1001::setup() {
  ESP_LOGCONFIG(TAG, "Setting up DFRobot C1001...");

  if (this->sensor_.begin() != 0) {
    ESP_LOGE(TAG, "Failed to initialize DFRobot C1001 sensor!");
  } else {
    ESP_LOGI(TAG, "Successfully initialized DFRobot C1001 sensor.");
  }
}

void DFRobotC1001::loop() {
  this->process_sensor_data();
}

void DFRobotC1001::dump_config() {
  ESP_LOGCONFIG(TAG, "DFRobot C1001:");
  LOG_UART_DEVICE(this);
}

void DFRobotC1001::process_sensor_data() {
  int presence = this->sensor_.smHumanData(DFRobot_HumanDetection::eHumanPresence);
  int movement = this->sensor_.smHumanData(DFRobot_HumanDetection::eHumanMovement);

  ESP_LOGD(TAG, "Presence: %d, Movement: %d", presence, movement);

  // Example: Log more data
  ESP_LOGD(TAG, "Breathe rate: %d", this->sensor_.getBreatheValue());
  ESP_LOGD(TAG, "Heart rate: %d", this->sensor_.getHeartRate());
}

}  // namespace dfrobot_c1001
}  // namespace esphome
