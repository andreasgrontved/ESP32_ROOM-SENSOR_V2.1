#pragma once

#include "esphome/core/automation.h"
#include "esphome/core/helpers.h"
#include "dfrobot_c1001.h"

namespace esphome {
namespace dfrobot_c1001 {

template<typename... Ts>
class DFRobotC1001ResetAction : public Action<Ts...>, public Parented<DFRobotC1001Component> {
 public:
  void play(Ts... x) { this->parent_->enqueue(make_unique<ResetSystemCommand>()); }
};

template<typename... Ts>
class DFRobotC1001SettingsAction : public Action<Ts...>, public Parented<DFRobotC1001Component> {
 public:
  TEMPLATABLE_VALUE(int8_t, factory_reset)
  TEMPLATABLE_VALUE(int8_t, start_after_power_on)
  TEMPLATABLE_VALUE(int8_t, turn_on_led)
  TEMPLATABLE_VALUE(int8_t, presence_via_uart)
  TEMPLATABLE_VALUE(int8_t, sensitivity)
  TEMPLATABLE_VALUE(uint16_t, installation_height)
  TEMPLATABLE_VALUE(uint16_t, fall_time)

  void play(Ts... x) {
    this->parent_->enqueue(make_unique<PowerCommand>(0));  // Stop the sensor before making changes

    if (this->factory_reset_.has_value() && this->factory_reset_.value(x...) == true) {
      this->parent_->enqueue(make_unique<FactoryResetCommand>());
    }
    if (this->installation_height_.has_value()) {
      uint16_t height = this->installation_height_.value(x...);
      this->parent_->enqueue(make_unique<SetInstallationHeightCommand>(height));
    }
    if (this->fall_time_.has_value()) {
      uint16_t time = this->fall_time_.value(x...);
      this->parent_->enqueue(make_unique<SetFallTimeCommand>(time));
    }
    if (this->start_after_power_on_.has_value()) {
      int8_t val = this->start_after_power_on_.value(x...);
      if (val >= 0) {
        this->parent_->enqueue(make_unique<SensorCfgStartCommand>(val));
      }
    }
    if (this->turn_on_led_.has_value()) {
      int8_t val = this->turn_on_led_.value(x...);
      if (val >= 0) {
        this->parent_->enqueue(make_unique<LedModeCommand>(val));
      }
    }
    if (this->presence_via_uart_.has_value()) {
      int8_t val = this->presence_via_uart_.value(x...);
      if (val >= 0) {
        this->parent_->enqueue(make_unique<UartOutputCommand>(val));
      }
    }
    if (this->sensitivity_.has_value()) {
      int8_t val = this->sensitivity_.value(x...);
      if (val >= 0) {
        if (val > 3) {
          val = 3;  // Limit sensitivity to the max value for this component
        }
        this->parent_->enqueue(make_unique<SetFallSensitivityCommand>(val));
      }
    }

    this->parent_->enqueue(make_unique<SaveConfigurationCommand>());  // Save configuration after making changes
    this->parent_->enqueue(make_unique<PowerCommand>(1));  // Restart the sensor after configuration
  }
};

}  // namespace dfrobot_c1001
}  // namespace esphome
