#include "dfrobot_c1001.h"

void DFRobotC1001::setup() {
  ESP_LOGI("DFRobotC1001", "Initializing DFRobot C1001...");

  while (this->hu_.begin() != 0) {
    ESP_LOGE("DFRobotC1001", "Initialization failed! Retrying...");
    delay(1000);
  }

  ESP_LOGI("DFRobotC1001", "Initialization successful!");

  // Configure work mode
  while (this->hu_.configWorkMode(this->hu_.eSleepMode) != 0) {
    ESP_LOGE("DFRobotC1001", "Failed to configure sleep mode! Retrying...");
    delay(1000);
  }

  this->hu_.configLEDLight(this->hu_.eHPLed, 1);  // Enable HP LED
  this->hu_.sensorRet();  // Reset the sensor to apply configuration
}

void DFRobotC1001::update() {
  // Read and publish human presence
  int presence = this->hu_.smHumanData(this->hu_.eHumanPresence);
  this->presence_sensor->publish_state(presence);

  // Read and publish motion information
  int motion = this->hu_.smHumanData(this->hu_.eHumanMovement);
  this->motion_sensor->publish_state(motion);

  // Read and publish body movement parameter
  int movement_param = this->hu_.smHumanData(this->hu_.eHumanMovingRange);
  this->movement_param_sensor->publish_state(movement_param);

  // Read and publish respiration rate
  int respiration_rate = this->hu_.getBreatheValue();
  this->respiration_rate_sensor->publish_state(respiration_rate);

  // Read and publish heart rate
  int heart_rate = this->hu_.gitHeartRate();
  this->heart_rate_sensor->publish_state(heart_rate);

  ESP_LOGI("DFRobotC1001", "Sensor data updated.");
}
