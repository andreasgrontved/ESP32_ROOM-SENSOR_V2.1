#pragma once

#include "esphome.h"
#include "DFRobot_HumanDetection.h"

namespace esphome {
namespace dfrobot_c1001 {

class DFRobotC1001 : public PollingComponent {
 public:
  DFRobotC1001() : PollingComponent(1000) {}

  void setup() override {
    Serial1.begin(115200, SERIAL_8N1, 17, 16);
    hu = new DFRobot_HumanDetection(&Serial1);

    while (hu->begin() != 0) {
      delay(1000);
    }

    while (hu->configWorkMode(hu->eSleepMode) != 0) {
      delay(1000);
    }

    hu->configLEDLight(hu->eHPLed, 1);
    hu->sensorRet();
  }

  void update() override {
    int presence = hu->smHumanData(hu->eHumanPresence);
    int movement = hu->smHumanData(hu->eHumanMovement);
    int moving_range = hu->smHumanData(hu->eHumanMovingRange);
    int breathe_value = hu->getBreatheValue();
    int heart_rate = hu->getHeartRate();

    presence_sensor->publish_state(presence);
    movement_sensor->publish_state(movement);
    moving_range_sensor->publish_state(moving_range);
    breathe_value_sensor->publish_state(breathe_value);
    heart_rate_sensor->publish_state(heart_rate);
  }

  Sensor *presence_sensor = new Sensor();
  Sensor *movement_sensor = new Sensor();
  Sensor *moving_range_sensor = new Sensor();
  Sensor *breathe_value_sensor = new Sensor();
  Sensor *heart_rate_sensor = new Sensor();

 private:
  DFRobot_HumanDetection *hu;
};

}  // namespace dfrobot_c1001
}  // namespace esphome