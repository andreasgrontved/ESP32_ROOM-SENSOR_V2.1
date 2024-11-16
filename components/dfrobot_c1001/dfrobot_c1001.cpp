#include "esphome/core/log.h"
#include "dfrobot_c1001.h"

namespace esphome {
namespace dfrobot_c1001 {

static const char *const TAG = "dfrobot_c1001";

void dfrobot_c1001::setup() {
  Serial1.begin(115200, SERIAL_8N1, 17, 16);
  hu = new DFRobot_HumanDetection(&Serial1);
  while (hu->begin() != 0) {
    ESP_LOGE(TAG, "Initialization error!!!");
    delay(1000);
  }
  ESP_LOGI(TAG, "Initialization successful");

  while (hu->configWorkMode(hu->eSleepMode) != 0) {
    ESP_LOGE(TAG, "Work mode switch error!!!");
    delay(1000);
  }
  ESP_LOGI(TAG, "Work mode switch successful");

  hu->configLEDLight(hu->eHPLed, 1);
  hu->sensorRet();
}

void dfrobot_c1001::loop() {
  int presence = hu->smHumanData(hu->eHumanPresence);
  int movement = hu->smHumanData(hu->eHumanMovement);
  int moving_range = hu->smHumanData(hu->eHumanMovingRange);
  int breathe_value = hu->getBreatheValue();
  int heart_rate = hu->getHeartRate();

  presence_sensor->publish_state(presence);
  movement_sensor->publish_state(movement);
  moving_range_sensor->publish_state(moving_range);
  breathe_value_sensor->publish_state(breathe_value);
  heart_rate_sensor->publish_state(heart_rate);
}

void dfrobot_c1001::dump_config(){
  ESP_LOGCONFIG(TAG, "DFRobot C1001:");
  LOG_SENSOR("  ", "Presence", this->presence_sensor);
  LOG_SENSOR("  ", "Movement", this->movement_sensor);
  LOG_SENSOR("  ", "Moving Range", this->moving_range_sensor);
  LOG_SENSOR("  ", "Respiration Rate", this->breathe_value_sensor);
  LOG_SENSOR("  ", "Heart Rate", this->heart_rate_sensor);
}

}  // namespace dfrobot_c1001
}  // namespace esphome


