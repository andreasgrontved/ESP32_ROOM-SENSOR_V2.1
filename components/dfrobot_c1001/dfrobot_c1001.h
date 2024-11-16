#pragma once

#include "esphome.h"
#include "DFRobot_HumanDetection.h"

namespace dfrobot_c1001 {

class DFRobot_HumanDetection : public esphome::Component {
 public:
  void set_uart_pins(int rx, int tx) {
    this->rx_pin = rx;
    this->tx_pin = tx;
  }

  void setup() override {
    Serial1.begin(115200, SERIAL_8N1, rx_pin, tx_pin);
    if (sensor.begin() != 0) {
      ESP_LOGE("DFRobot_HumanDetection", "Initialization failed!");
    } else {
      ESP_LOGI("DFRobot_HumanDetection", "Initialization successful");
    }
  }

  void loop() override {
    int presence = sensor.smHumanData(sensor.eHumanPresence);
    int movement = sensor.smHumanData(sensor.eHumanMovement);

    ESP_LOGD("DFRobot_HumanDetection", "Presence: %d, Movement: %d", presence, movement);
  }

 private:
  int rx_pin;
  int tx_pin;
  ::DFRobot_HumanDetection sensor{&Serial1};
};

}  // namespace dfrobot_c1001
