#include "dfrobot_c1001.h"
#include "esphome/core/log.h"

namespace esphome {
namespace dfrobot_c1001 {

static const char *const TAG = "dfrobot_c1001";

void DFRobotC1001Component::setup() {
  Serial1.begin(115200, SERIAL_8N1, 17, 16);
  hu = new DFRobot_HumanDetection(&Serial1);

  while (hu->begin() != 0) {
    ESP_LOGE(TAG, "Initialization error!!!");
    delay(1000);
  }
  ESP_LOGI(TAG, "Initialization successful");

  if (height_number_ != nullptr) {
    hu->dmInstallHeight(static_cast<uint16_t>(height_number_->state));
  }

  if (work_mode_switch_ != nullptr) {
    hu->configWorkMode(work_mode_switch_->state ? hu->eSleepMode : hu->eNormalMode);
  }
}

void DFRobotC1001Component::update() {
  int presence = hu->smHumanData(hu->eHumanPresence);
  int movement = hu->smHumanData(hu->eHumanMovement);
  int moving_range = hu->smHumanData(hu->eHumanMovingRange);
  int breathe_value = hu->getBreatheValue();
  int heart_rate = hu->getHeartRate();

  if (presence_sensor_ != nullptr) presence_sensor_->publish_state(presence);
  if (movement_sensor_ != nullptr) movement_sensor_->publish_state(movement);
  if (moving_range_sensor_ != nullptr) moving_range_sensor_->publish_state(moving_range);
  if (breathe_value_sensor_ != nullptr) breathe_value_sensor_->publish_state(breathe_value);
  if (heart_rate_sensor_ != nullptr) heart_rate_sensor_->publish_state(heart_rate);
}

void DFRobotC1001Component::dump_config() {
  ESP_LOGCONFIG(TAG, "DFRobot C1001:");
  LOG_SENSOR("  ", "Presence", this->presence_sensor_);
  LOG_SENSOR("  ", "Movement", this->movement_sensor_);
  LOG_SENSOR("  ", "Moving Range", this->moving_range_sensor_);
  LOG_SENSOR("  ", "Respiration Rate", this->breathe_value_sensor_);
  LOG_SENSOR("  ", "Heart Rate", this->heart_rate_sensor_);
  LOG_NUMBER("  ", "Height", this->height_number_);
  LOG_SWITCH("  ", "Work Mode", this->work_mode_switch_);
}

}  // namespace dfrobot_c1001
}  // namespace esphome