#include "esphome/core/log.h"
#include "dfrobot_c1001.h"

namespace esphome {
namespace dfrobot_c1001 {

static const char *TAG = "dfrobot_c1001";

DFRobotC1001::DFRobotC1001(uart::UARTComponent *parent)
    : UARTDevice(parent), hu_(this->get_stream()) {}

void DFRobotC1001::setup() {
  ESP_LOGI(TAG, "Initializing sensor");
  while (hu_.begin() != 0) {
    ESP_LOGE(TAG, "Sensor initialization failed, retrying...");
    delay(1000);
  }
  ESP_LOGI(TAG, "Sensor initialized successfully");

  ESP_LOGI(TAG, "Configuring work mode to Sleep Mode");
  while (hu_.configWorkMode(hu_.eSleepMode) != 0) {
    ESP_LOGE(TAG, "Error setting work mode, retrying...");
    delay(1000);
  }
  ESP_LOGI(TAG, "Work mode configured successfully");

  hu_.configLEDLight(hu_.eHPLed, 1);
  hu_.sensorRet();
}

void DFRobotC1001::loop() {
  int presence = hu_.smHumanData(hu_.eHumanPresence);
  if (this->presence_binary_sensor != nullptr) {
    this->presence_binary_sensor->publish_state(presence == 1);
  }

  int motion = hu_.smHumanData(hu_.eHumanMovement);
  if (this->motion_sensor != nullptr) {
    this->motion_sensor->publish_state(motion);
  }

  int movement_param = hu_.smHumanData(hu_.eHumanMovingRange);
  if (this->movement_param_sensor != nullptr) {
    this->movement_param_sensor->publish_state(movement_param);
  }

  int respiration_rate = hu_.getBreatheValue();
  if (this->respiration_rate_sensor != nullptr) {
    this->respiration_rate_sensor->publish_state(respiration_rate);
  }

  int heart_rate = hu_.getHeartRate();
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
