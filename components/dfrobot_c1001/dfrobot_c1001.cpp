#include "esphome/core/log.h"
#include "dfrobot_c1001.h"
#include "DFRobot_HumanDetection.h"

namespace esphome {
namespace dfrobot_c1001 {

static const char *TAG = "dfrobot_c1001.component";

dfrobot_c1001::dfrobot_c1001(uart::UARTComponent *parent)
    : UARTDevice(parent), hu_(this->get_stream()) {

DFRobot_HumanDetection hu(&Serial1);

void dfrobot_c1001::setup() {  
  ESP_LOGCONFIG(TAG, "Start initialization");
  while (hu.begin() != 0) {
    ESP_LOGCONFIG(TAG, "init error!!!");
    delay(1000);
  }
  ESP_LOGCONFIG(TAG,"Initialization successful");

  ESP_LOGCONFIG(TAG,"Start switching work mode");
  while (hu.configWorkMode(hu.eSleepMode) != 0) {
    ESP_LOGCONFIG(TAG,"error!!!");
    delay(1000);
  }
  ESP_LOGCONFIG(TAG,"Work mode switch successful");

  ESP_LOGCONFIG(TAG,"Current work mode:");
  switch (hu.getWorkMode()) {
    case 1:
      ESP_LOGCONFIG(TAG,"Fall detection mode");
      break;
    case 2:
      ESP_LOGCONFIG(TAG,"Sleep detection mode");
      break;
    default:
      ESP_LOGCONFIG(TAG,"Read error");
  }

  hu.configLEDLight(hu.eHPLed, 1);  // Set HP LED switch, it will not light up even if the sensor detects a person when set to 0.
  hu.sensorRet();                   // Module reset, must perform sensorRet after setting data, otherwise the sensor may not be usable

  ESP_LOGCONFIG(TAG,"HP LED status:");
  switch (hu.getLEDLightState(hu.eHPLed)) {
    case 0:
      ESP_LOGCONFIG(TAG,"Off");
      break;
    case 1:
      ESP_LOGCONFIG(TAG,"On");
      break;
    default:
      ESP_LOGCONFIG(TAG,"Read error");
  }

}

void dfrobot_c1001::loop() {
Serial.print("Existing information:");
  switch (hu.smHumanData(hu.eHumanPresence)) {
    case 0:
      Serial.println("No one is present");
      break;
    case 1:
      Serial.println("Someone is present");
      break;
    default:
      Serial.println("Read error");
  }

  Serial.print("Motion information:");
  switch (hu.smHumanData(hu.eHumanMovement)) {
    case 0:
      ESP_LOGCONFIG(TAG,"None");
      break;
    case 1:
      ESP_LOGCONFIG(TAG,"Still");
      break;
    case 2:
      ESP_LOGCONFIG(TAG,"Active");
      break;
    default:
      ESP_LOGCONFIG(TAG,"Read error");
  }

  ESP_LOGCONFIG(TAG,"Body movement parameters: ");
  ESP_LOGCONFIG(TAG,hu.smHumanData(hu.eHumanMovingRange));
  ESP_LOGCONFIG(TAG,"Respiration rate: ");
  ESP_LOGCONFIG(TAG,hu.getBreatheValue());
  ESP_LOGCONFIG(TAG,"Heart rate: ");
  ESP_LOGCONFIG(TAG,hu.getHeartRate());
  ESP_LOGCONFIG(TAG,"-----------------------");
  delay(1000);
}
}

void dfrobot_c1001::dump_config(){
    ESP_LOGCONFIG(TAG, "dfrobot_c1001");
}

}  // namespace dfrobot_c1001
}  // namespace esphome