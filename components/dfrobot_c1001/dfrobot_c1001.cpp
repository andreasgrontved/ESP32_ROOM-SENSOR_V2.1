#include "esphome/core/log.h"
#include "dfrobot_c1001.h"

namespace esphome {
namespace dfrobot_c1001 {

static const char *TAG = "dfrobot_c1001";

DFRobotC1001::DFRobotC1001(uart::UARTComponent *parent)
    : UARTDevice(parent), hu_(this->get_stream()) {
  // Initialize sensors
  this->presence_binary_sensor = new esphome::binary_sensor::BinarySensor();
  this->motion_sensor = new esphome::sensor::Sensor();
  this->movement_param_sensor = new esphome::sensor::Sensor();
  this->respiration_rate_sensor = new esphome::sensor::Sensor();
  this->heart_rate_sensor = new esphome::sensor::Sensor();
}

void DFRobotC1001::setup() {
  ESP_LOGI(TAG, "Initializing sensor");
  while (this->hu_.begin() != 0) {
    ESP_LOGE(TAG, "Sensor initialization failed, retrying...");
    delay(1000);
  }
  ESP_LOGI(TAG, "Sensor initialized successfully");

  ESP_LOGI(TAG, "Configuring work mode to Sleep Mode");
  while (this->hu_.configWorkMode(this->hu_.eSleepMode) != 0) {
    ESP_LOGE(TAG, "Error setting work mode, retrying...");
    delay(1000);
  }
  ESP_LOGI(TAG, "Work mode configured successfully");

  this->hu_.configLEDLight(this->hu_.eHPLed, 1);
  this->hu_.sensorRet();
}

void DFRobotC1001::loop() {
  int presence = this->hu_.smHumanData(this->hu_.eHumanPresence);
  if (this->presence_binary_sensor != nullptr) {
    this->presence_binary_sensor->publish_state(presence == 1);
  }

  int motion = this->hu_.smHumanData(this->hu_.eHumanMovement);
  if (this->motion_sensor != nullptr) {
    this->motion_sensor->publish_state(motion);
  }

  int movement_param = this->hu_.smHumanData(this->hu_.eHumanMovingRange);
  if (this->movement_param_sensor != nullptr) {
    this->movement_param_sensor->publish_state(movement_param);
  }

  int respiration_rate = this->hu_.getBreatheValue();
  if (this->respiration_rate_sensor != nullptr) {
    this->respiration_rate_sensor->publish_state(respiration_rate);
  }

  int heart_rate = this->hu_.getHeartRate();
  if (this->heart_rate_sensor != nullptr) {
    this->heart_rate_sensor->publish_state(heart_rate);
  }

  ESP_LOGD(TAG, "Presence: %d, Motion: %d, Movement Param: %d, Respiration Rate: %d, Heart Rate: %d",
           presence, motion, movement_param, respiration_rate, heart_rate);
}

void DFRobotC1001::dump_config() {
  ESP_LOGCONFIG(TAG, "DFRobot C1001 Sensor");
  LOG_UART_DEVICE(this);
}

}  // namespace dfrobot_c1001
}  // namespace esphome
