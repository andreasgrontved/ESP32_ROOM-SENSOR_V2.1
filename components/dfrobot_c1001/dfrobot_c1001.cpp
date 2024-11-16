#include "esphome/core/log.h"
#include "dfrobot_c1001.h"
#include "DFRobot_HumanDetection.h"

namespace esphome {
namespace dfrobot_c1001 {

static const char *TAG = "dfrobot_c1001";

void DFRobotC1001::setup() {
  if (!this->is_uart_initialised()) {
    ESP_LOGE(TAG, "UART not initialized! Check your UART settings.");
    return;
  }

  ESP_LOGI(TAG, "Starting DFRobot C1001 sensor initialization");

  if (hu.begin(this->get_uart()) != 0) {
    ESP_LOGE(TAG, "Sensor initialization failed! Retrying...");
    return;
  }

  ESP_LOGI(TAG, "DFRobot C1001 initialization successful");
  hu.configLEDLight(hu.eHPLed, 1);  // Enable LED light as part of setup
  hu.sensorRet();
}

void DFRobotC1001::loop() {
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

  delay(1000);
}

void DFRobotC1001::dump_config() {
  ESP_LOGCONFIG(TAG, "DFRobot C1001 Sensor:");
  LOG_SENSOR("  ", "Presence Sensor", this->presence_sensor_);
  LOG_SENSOR("  ", "Movement Sensor", this->movement_sensor_);
  LOG_SENSOR("  ", "Movement Parameter Sensor", this->movement_param_sensor_);
  LOG_SENSOR("  ", "Respiration Rate Sensor", this->respiration_rate_sensor_);
  LOG_SENSOR("  ", "Heart Rate Sensor", this->heart_rate_sensor_);
}

}  // namespace dfrobot_c1001
}  // namespace esphome