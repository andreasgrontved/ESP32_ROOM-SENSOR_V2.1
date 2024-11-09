#include "esphome/core/log.h"
#include "dfrobot_c1001.h"

namespace esphome {
namespace dfrobot_c1001 {

static const char *TAG = "dfrobot_c1001.component";

void dfrobot_c1001::setup() {
  ESP_LOGI(TAG, "Setting up DFRobot C1001 component...");

  Serial1.begin(115200, SERIAL_8N1, 4, 17);  // RX: GPIO4, TX: GPIO17

  // Initialize sensor
  if (hu.begin() != 0) {
    ESP_LOGE(TAG, "Failed to initialize the sensor!");
  } else {
    ESP_LOGI(TAG, "Sensor initialized successfully.");
  }

  // Set initial settings
  this->set_led_enabled(led_enabled_);
  this->set_fall_sensitivity(fall_sensitivity_);
  this->set_installation_height(installation_height_);
}

void dfrobot_c1001::loop() {

}

void dfrobot_c1001::dump_config(){
    ESP_LOGCONFIG(TAG, "dfrobot_c1001");
}

void DFRobotC1001Component::set_led_enabled(bool enabled) {
  led_enabled_ = enabled;
  hu.configLEDLight(hu.eHPLed, enabled ? 1 : 0);
  hu.configLEDLight(hu.eFALLLed, enabled ? 1 : 0);
}

void DFRobotC1001Component::set_fall_sensitivity(int sensitivity) {
  fall_sensitivity_ = sensitivity;
  hu.dmFallConfig(hu.eFallSensitivityC, sensitivity);
}

void DFRobotC1001Component::set_installation_height(int height_cm) {
  installation_height_ = height_cm;
  hu.dmInstallHeight(height_cm);
}

int DFRobotC1001Component::get_presence_status() {
  return hu.smHumanData(hu.eHumanPresence);
}

int DFRobotC1001Component::get_motion_status() {
  return hu.smHumanData(hu.eHumanMovement);
}

int DFRobotC1001Component::get_fall_status() {
  return hu.getFallData(hu.eFallState);
}

int DFRobotC1001Component::get_residency_status() {
  return hu.getFallData(hu.estaticResidencyState);
}


}  // namespace dfrobot_c1001
}  // namespace esphome
