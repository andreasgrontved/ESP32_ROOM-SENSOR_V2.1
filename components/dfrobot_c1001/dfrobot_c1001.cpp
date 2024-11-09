#include "esphome/core/log.h"
#include "dfrobot_c1001.h"

namespace esphome {
namespace dfrobot_c1001 {

static const char *TAG = "dfrobot_c1001.component";

DFRobotC1001::DFRobotC1001(HardwareSerial* serial) : UARTDevice(serial), hu_(serial) {}



void DFRobotC1001::setup() {
  ESP_LOGCONFIG(TAG, "Setting up DFRobot C1001...");

  if (hu_.begin() != 0) {
    ESP_LOGE(TAG, "Initialization failed!");
    return;
  }
  ESP_LOGCONFIG(TAG, "Initialization successful.");

  // Default configuration
  hu_.configWorkMode(hu_.eFallingMode);
  hu_.configLEDLight(hu_.eFALLLed, 1);
  hu_.dmInstallHeight(270);
  hu_.dmFallTime(5);
  hu_.dmFallConfig(hu_.eResidenceTime, 200);
  hu_.dmFallConfig(hu_.eFallSensitivityC, 3);
  hu_.sensorRet();  // Apply settings
}

void DFRobotC1001::loop() {
  // Poll sensor data every loop and log it
  uint16_t presence = get_human_presence();
  uint8_t heart_rate = get_heart_rate();
  uint8_t breathe_state = get_breathe_state();

  // Log sensor data (or publish to Home Assistant entities)
  ESP_LOGD(TAG, "Presence: %d, Heart Rate: %d, Breathe State: %d", presence, heart_rate, breathe_state);
}

void DFRobotC1001::dump_config() {
  ESP_LOGCONFIG(TAG, "DFRobot C1001:");
  ESP_LOGCONFIG(TAG, "  Work mode: %d", get_work_mode());
}

void DFRobotC1001::set_work_mode(DFRobot_HumanDetection::eWorkMode mode) {
  hu_.configWorkMode(mode);
}

void DFRobotC1001::set_led_state(DFRobot_HumanDetection::eLed led, uint8_t state) {
  hu_.configLEDLight(led, state);
}

void DFRobotC1001::set_installation_height(uint16_t height) {
  hu_.dmInstallHeight(height);
}

void DFRobotC1001::set_fall_sensitivity(uint8_t sensitivity) {
  hu_.dmFallConfig(hu_.eFallSensitivityC, sensitivity);
}

void DFRobotC1001::set_fall_time(uint16_t time) {
  hu_.dmFallTime(time);
}

// Data retrieval methods
uint8_t DFRobotC1001::get_work_mode() {
  return hu_.getWorkMode();
}

uint8_t DFRobotC1001::get_led_state(DFRobot_HumanDetection::eLed led) {
  return hu_.getLEDLightState(led);
}

uint16_t DFRobotC1001::get_human_presence() {
  return hu_.smHumanData(hu_.eHumanPresence);
}

uint8_t DFRobotC1001::get_heart_rate() {
  return hu_.getHeartRate();
}

uint8_t DFRobotC1001::get_breathe_state() {
  return hu_.getBreatheState();
}

sSleepComposite DFRobotC1001::get_sleep_composite() {
  return hu_.getSleepComposite();
}

sSleepStatistics DFRobotC1001::get_sleep_statistics() {
  return hu_.getSleepStatistics();
}

}  // namespace dfrobot_c1001
}  // namespace esphome
