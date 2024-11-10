#include "dfrobot_c1001_switch.h"

namespace esphome {
namespace dfrobot_c1001 {

void C1001PowerSwitch::write_state(bool state) { 
  this->parent_->enqueue(make_unique<PowerCommand>(state)); 
}

void C1001LedSwitch::write_state(bool state) {
  bool was_active = false;
  if (this->parent_->is_active()) {
    was_active = true;
    this->parent_->enqueue(make_unique<PowerCommand>(false));
  }
  this->parent_->enqueue(make_unique<LedModeCommand>(state));
  this->parent_->enqueue(make_unique<SaveCfgCommand>());
  if (was_active) {
    this->parent_->enqueue(make_unique<PowerCommand>(true));
  }
}

void C1001UartPresenceSwitch::write_state(bool state) {
  bool was_active = false;
  if (this->parent_->is_active()) {
    was_active = true;
    this->parent_->enqueue(make_unique<PowerCommand>(false));
  }
  this->parent_->enqueue(make_unique<UartOutputCommand>(state));
  this->parent_->enqueue(make_unique<SaveCfgCommand>());
  if (was_active) {
    this->parent_->enqueue(make_unique<PowerCommand>(true));
  }
}

void C1001StartAfterBootSwitch::write_state(bool state) {
  bool was_active = false;
  if (this->parent_->is_active()) {
    was_active = true;
    this->parent_->enqueue(make_unique<PowerCommand>(false));
  }
  this->parent_->enqueue(make_unique<SensorCfgStartCommand>(state));
  this->parent_->enqueue(make_unique<SaveCfgCommand>());
  if (was_active) {
    this->parent_->enqueue(make_unique<PowerCommand>(true));
  }
}

}  // namespace dfrobot_c1001
}  // namespace esphome
