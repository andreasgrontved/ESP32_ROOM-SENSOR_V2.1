#include "dfrobot_c1001.h"

namespace esphome {
namespace dfrobot_c1001 {

void DFRobotC1001::setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 17, 16);

  ESP_LOGD("DFRobotC1001", "Start initialization");
  while (hu.begin() != 0) {
    ESP_LOGE("DFRobotC1001", "init error!!!");
    delay(1000);
  }
  ESP_LOGD("DFRobotC1001", "Initialization successful");

  ESP_LOGD("DFRobotC1001", "Start switching work mode");
  while (hu.configWorkMode(hu.eSleepMode) != 0) {
    ESP_LOGE("DFRobotC1001", "error!!!");
    delay(1000);
  }
  ESP_LOGD("DFRobotC1001", "Work mode switch successful");

  ESP_LOGD("DFRobotC1001", "Current work mode: %d", hu.getWorkMode());

  hu.configLEDLight(hu.eHPLed, 1);
  hu.sensorRet();
  ESP_LOGD("DFRobotC1001", "HP LED status: %d", hu.getLEDLightState(hu.eHPLed));
}

void DFRobotC1001::update() {
  ESP_LOGD("DFRobotC1001", "Existing information: %d", hu.smHumanData(hu.eHumanPresence));
  ESP_LOGD("DFRobotC1001", "Motion information: %d", hu.smHumanData(hu.eHumanMovement));
  ESP_LOGD("DFRobotC1001", "Body movement parameters: %d", hu.smHumanData(hu.eHumanMovingRange));
  ESP_LOGD("DFRobotC1001", "Respiration rate: %d", hu.getBreatheValue());
  ESP_LOGD("DFRobotC1001", "Heart rate: %d", hu.getHeartRate());
  delay(1000);
}

void DFRobotC1001::init() {
  // Additional initialization if necessary
}

}  // namespace dfrobot_c1001
}  // namespace esphome