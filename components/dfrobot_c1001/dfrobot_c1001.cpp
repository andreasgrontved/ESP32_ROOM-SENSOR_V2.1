#include "dfrobot_c1001.h"
#include "esphome/core/log.h"

namespace esphome {
namespace dfrobot_c1001 {

DFRobotC1001Component::DFRobotC1001Component(uart::UARTComponent *parent) : UARTDevice(parent), hu_(&parent->get_uart()) {}

void DFRobotC1001Component::setup() {
  ESP_LOGI("DFRobotC1001", "Initializing DFRobot C1001...");
  while (this->hu_.begin() != 0) {
    ESP_LOGE("DFRobotC1001", "Initialization failed! Retrying...");
    delay(1000);
  }
  ESP_LOGI("DFRobotC1001", "Initialization successful!");
  this->hu_.configWorkMode(this->hu_.eSleepMode);
  this->hu_.configLEDLight(this->hu_.eHPLed, 1);
  this->hu_.sensorRet();
}

void DFRobotC1001Component::loop() {
  if (this->presence_sensor_ != nullptr) {
    this->presence_sensor_->publish_state(this->hu_.smHumanData(this->hu_.eHumanPresence));
  }
  if (this->motion_sensor_ != nullptr) {
    this->motion_sensor_->publish_state(this->hu_.smHumanData(this->hu_.eHumanMovement));
  }
  if (this->movement_param_sensor_ != nullptr) {
    this->movement_param_sensor_->publish_state(this->hu_.smHumanData(this->hu_.eHumanMovingRange));
  }
  if (this->respiration_rate_sensor_ != nullptr) {
    this->respiration_rate_sensor_->publish_state(this->hu_.getBreatheValue());
  }
  if (this->heart_rate_sensor_ != nullptr) {
    this->heart_rate_sensor_->publish_state(this->hu_.getHeartRate());
}

}  // namespace dfrobot_c1001
}  // namespace esphome