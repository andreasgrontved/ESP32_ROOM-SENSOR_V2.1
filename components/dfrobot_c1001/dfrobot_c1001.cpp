#include "esphome/core/log.h"
#include "dfrobot_c1001.h"
#include "DFRobot_HumanDetection.h"
#include "DFRobot_HumanDetection.cpp"

DFRobot_HumanDetection hu(&Serial1);

namespace esphome {
namespace dfrobot_c1001 {

static const char *TAG = "dfrobot_c1001.sensor";

void dfrobot_c1001::setup() {
ESP_LOGI(TAG, "Starting initialization...");

  #if defined(ESP32)
    Serial1.begin(115200, SERIAL_8N1, 2, 4);  // Use GPIO4 as RX and GPIO5 as TX
  #else
    Serial1.begin(115200);
  #endif

  // Initialize the sensor with retry
  while (hu.begin() != 0) {
    ESP_LOGW(TAG, "Initialization error, retrying...");
    delay(1000);
  }
  ESP_LOGI(TAG, "Initialization successful");

  // Switch work mode to sleep mode with retry
  ESP_LOGI(TAG, "Start switching work mode...");
  while (hu.configWorkMode(hu.eSleepMode) != 0) {
    ESP_LOGW(TAG, "Work mode switch error, retrying...");
    delay(1000);
  }
  ESP_LOGI(TAG, "Work mode switch successful");

  // Log current work mode
  int work_mode = hu.getWorkMode();
  switch (work_mode) {
    case 1:
      ESP_LOGI(TAG, "Current work mode: Fall detection mode");
      break;
    case 2:
      ESP_LOGI(TAG, "Current work mode: Sleep detection mode");
      break;
    default:
      ESP_LOGW(TAG, "Work mode: Read error");
  }

  // Configure and log LED status
  hu.configLEDLight(hu.eHPLed, 1);
  hu.sensorRet();
  
  int led_status = hu.getLEDLightState(hu.eHPLed);
  switch (led_status) {
    case 0:
      ESP_LOGI(TAG, "HP LED status: Off");
      break;
    case 1:
      ESP_LOGI(TAG, "HP LED status: On");
      break;
    default:
      ESP_LOGW(TAG, "HP LED status: Read error");
  }
}


void dfrobot_c1001::update() {
 
 int presence = hu.smHumanData(hu.eHumanPresence);

  // Convert the presence data to a readable format
  const char *presence_str;
  switch (presence) {
    case 0:
      presence_str = "No one is present";
      this->publish_state(0);
      break;
    case 1:
      presence_str = "Someone is present";
      this->publish_state(1);
      break;
    default:
      presence_str = "Read error";
      this->publish_state(-1);
      break;
  }

 int motion = hu.smHumanData(hu.eHumanMovement);

  // Convert the motion data to a readable format
  const char *motion_str;
  switch (motion) {
    case 0:
      motion_str = "None";
      this->publish_state(0);
      break;
    case 1:
      motion_str = "Still";
      this->publish_state(1);
      break;
    case 2:
      motion_str = "Active";
      this->publish_state(2);
      break;
    default:
      motion_str = "Read error";
      this->publish_state(-1);
      break;
}
}

void dfrobot_c1001::loop() {
}

void dfrobot_c1001::dump_config(){
    ESP_LOGCONFIG(TAG, "dfrobot_c1001");
}

}  // namespace dfrobot_c1001
}  // namespace esphome