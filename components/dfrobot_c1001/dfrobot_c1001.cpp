#include "esphome/core/log.h"
#include "dfrobot_c1001.h"
#include "DFRobot_HumanDetection.h"

namespace esphome {
namespace dfrobot_c1001 {

static const char *TAG = "dfrobot_c1001.component";


void dfrobot_c1001::setup() {
  // Retrieve the UART component defined in the ESPHome YAML
  auto *uart_bus = this->uart_bus_;
  if (uart_bus == nullptr) {
    ESP_LOGE(TAG, "UART bus not found! Initialization failed.");
    return;
  }

  ESP_LOGI(TAG, "Start initialization");

  // Replace 'hu' with the specific initialization function for your device
  while (hu.begin(uart_bus) != 0) {  // Example: initialize 'hu' with UART
    ESP_LOGE(TAG, "Init error!!! Retrying...");
    delay(1000);
  }
  
  ESP_LOGI(TAG, "Initialization successful");

  ESP_LOGI(TAG,"Start switching work mode");
  while (hu.configWorkMode(hu.eSleepMode) != 0) {
    ESP_LOGI(TAG,"error!!!");
    delay(1000);
  }
  ESP_LOGI(TAG,"Work mode switch successful");

  ESP_LOGI(TAG,"Current work mode:");
  switch (hu.getWorkMode()) {
    case 1:
      ESP_LOGI(TAG,"Fall detection mode");
      break;
    case 2:
      ESP_LOGI(TAG,"Sleep detection mode");
      break;
    default:
      ESP_LOGI(TAG,"Read error");
  }

  hu.configLEDLight(hu.eHPLed, 1);  // Set HP LED switch, it will not light up even if the sensor detects a person when set to 0.
  hu.sensorRet();                   // Module reset, must perform sensorRet after setting data, otherwise the sensor may not be usable

  ESP_LOGI(TAG,"HP LED status:");
  switch (hu.getLEDLightState(hu.eHPLed)) {
    case 0:
      ESP_LOGI(TAG,"Off");
      break;
    case 1:
      ESP_LOGI(TAG,"On");
      break;
    default:
      ESP_LOGI(TAG,"Read error");
  }

}

void dfrobot_c1001::loop() {
ESP_LOGI(TAG,"Existing information:");
  switch (hu.smHumanData(hu.eHumanPresence)) {
    case 0:
      ESP_LOGI(TAG,"No one is present");
      break;
    case 1:
      ESP_LOGI(TAG,"Someone is present");
      break;
    default:
      ESP_LOGI(TAG,"Read error");
  }

  ESP_LOGI(TAG,"Motion information:");
  switch (hu.smHumanData(hu.eHumanMovement)) {
    case 0:
      ESP_LOGI(TAG,"None");
      break;
    case 1:
      ESP_LOGI(TAG,"Still");
      break;
    case 2:
      ESP_LOGI(TAG,"Active");
      break;
    default:
      ESP_LOGI(TAG,"Read error");
  }

  ESP_LOGI(TAG,"Body movement parameters: ");
  ESP_LOGI(TAG,hu.smHumanData(hu.eHumanMovingRange));
  ESP_LOGI(TAG,"Respiration rate: ");
  ESP_LOGI(TAG,hu.getBreatheValue());
  ESP_LOGI(TAG,"Heart rate: ");
  ESP_LOGI(TAG,hu.getHeartRate());
  ESP_LOGI(TAG,"-----------------------");
  delay(1000);
}


void dfrobot_c1001::dump_config(){
    ESP_LOGCONFIG(TAG, "dfrobot_c1001");
}

}  // namespace dfrobot_c1001
}  // namespace esphome