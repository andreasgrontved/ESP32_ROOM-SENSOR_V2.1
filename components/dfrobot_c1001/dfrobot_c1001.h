#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "DFRobot_HumanDetection.h"  // Include the DFRobot library


namespace esphome {
namespace dfrobot_c1001 {

class DFRobotC1001 : public uart::UARTDevice, public Component {
 public:
  DFRobotC1001(UARTComponent *parent);

  void setup() override;
  void loop() override;
  void dump_config() override;

  // Configuration methods
  void set_work_mode(DFRobot_HumanDetection::eWorkMode mode);
  void set_led_state(DFRobot_HumanDetection::eLed led, uint8_t state);
  void set_installation_height(uint16_t height);
  void set_fall_sensitivity(uint8_t sensitivity);
  void set_fall_time(uint16_t time);

  // Data retrieval methods
  uint8_t get_work_mode();
  uint8_t get_led_state(DFRobot_HumanDetection::eLed led);
  uint16_t get_human_presence();
  uint8_t get_heart_rate();
  uint8_t get_breathe_state();
  sSleepComposite get_sleep_composite();
  sSleepStatistics get_sleep_statistics();

 private:
  DFRobot_HumanDetection hu_;
};

}  // namespace dfrobot_c1001
}  // namespace esphome