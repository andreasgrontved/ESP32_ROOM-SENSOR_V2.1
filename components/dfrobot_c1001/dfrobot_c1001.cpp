#include "esphome/core/log.h"
#include "dfrobot_c1001.h"
#include "DFRobot_HumanDetection.h"

namespace esphome {
namespace dfrobot_c1001 {

static const char *TAG = "dfrobot_c1001.component";

void DFRobotC1001::setup() {
  auto *uart_bus = this->uart_bus_;
  if (uart_bus == nullptr) {
    ESP_LOGE(TAG, "UART bus not found! Initialization failed.");
    return;
  }

  ESP_LOGI(TAG, "Start initialization");

  while (hu.begin(uart_bus) != 0) {
    ESP_LOGE(TAG, "Init error!!! Retrying...");
    delay(1000);
  }
  
  ESP_LOGI(TAG, "Initialization successful");

  hu.configLEDLight(hu.eHPLed, 1);  
  hu.sensorRet();
}

void DFRobotC1001::update() {
  if (this->presence_sensor_)
    this->presence_sensor_->publish_state(hu.smHumanData(hu.eHumanPresence) == 1);

  if (this->movement_sensor_) {
    int movement = hu.smHumanData(hu.eHumanMovement);
    this->movement_sensor_->publish_state(movement == 1 ? "Still" : (movement == 2 ? "Active" : "None"));
  }

  if (this->movement_param_sensor_)
    this->movement_param_sensor_->publish_state(hu.smHumanData(hu.eHumanMovingRange));

  if (this->respiration_rate_sensor_)
    this->respiration_rate_sensor_->publish_state(hu.getBreatheValue());

  if (this->heart_rate_sensor_)
    this->heart_rate_sensor_->publish_state(hu.getHeartRate());
}

void DFRobotC1001::dump_config() {
  ESP_LOGCONFIG(TAG, "DFRobot C1001 Sensor");
  LOG_SENSOR("  ", "Presence Sensor", this->presence_sensor_);
  LOG_SENSOR("  ", "Movement Sensor", this->movement_sensor_);
  LOG_SENSOR("  ", "Movement Parameter", this->movement_param_sensor_);
  LOG_SENSOR("  ", "Respiration Rate", this->respiration_rate_sensor_);
  LOG_SENSOR("  ", "Heart Rate", this->heart_rate_sensor_);
}

}  // namespace dfrobot_c1001
}  // namespace esphome
