#include "dfrobot_c1001.h"

namespace esphome {

DFRobotC1001::DFRobotC1001(uart::UARTComponent *parent) : UARTDevice(parent), hu_(&parent->get_uart()) {}

void DFRobotC1001::setup() {
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

void DFRobotC1001::loop() {
  this->presence_sensor->publish_state(this->hu_.smHumanData(this->hu_.eHumanPresence));
  this->motion_sensor->publish_state(this->hu_.smHumanData(this->hu_.eHumanMovement));
  this->movement_param_sensor->publish_state(this->hu_.smHumanData(this->hu_.eHumanMovingRange));
  this->respiration_rate_sensor->publish_state(this->hu_.getBreatheValue());
  this->heart_rate_sensor->publish_state(this->hu_.gitHeartRate());
}

}  // namespace esphome

