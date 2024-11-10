#include "dfrobot_c1001.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace dfrobot_c1001 {

static const char *const TAG = "dfrobot_c1001";
const char ASCII_CR = 0x0D;
const char ASCII_LF = 0x0A;

void DFRobotC1001Component::dump_config() {
  ESP_LOGCONFIG(TAG, "DFRobot C1001 Sensor:");
#ifdef USE_BINARY_SENSOR
  LOG_BINARY_SENSOR("  ", "Presence Detected", this->presence_binary_sensor_);
#endif
#ifdef USE_SWITCH
  LOG_SWITCH("  ", "Sensor Active", this->sensor_active_switch_);
  LOG_SWITCH("  ", "Turn on LED", this->turn_on_led_switch_);
  LOG_SWITCH("  ", "Fall Detection Enabled", this->fall_detection_switch_);
#endif
  ESP_LOGCONFIG(TAG, "  Installation Height: %d cm", this->installation_height_);
  ESP_LOGCONFIG(TAG, "  Fall Sensitivity: %d", this->fall_sensitivity_);
}

void DFRobotC1001Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up DFRobot C1001...");
  if (this->hu_.begin() != 0) {
    ESP_LOGE(TAG, "Sensor initialization failed!");
    return;
  }
  ESP_LOGCONFIG(TAG, "Sensor initialized successfully.");

  // Default configuration setup for sensor
  this->hu_.configWorkMode(this->hu_.eFallingMode);
  this->hu_.configLEDLight(this->hu_.eFALLLed, this->led_active_);
  this->hu_.dmInstallHeight(this->installation_height_);
  this->hu_.dmFallConfig(this->hu_.eFallSensitivityC, this->fall_sensitivity_);
  this->hu_.sensorRet();  // Apply settings
}

void DFRobotC1001Component::loop() {
  this->process_data_();  // Process incoming sensor data
}

void DFRobotC1001Component::process_data_() {
  if (this->read_message_()) {
    uint16_t presence = this->hu_.smHumanData(this->hu_.eHumanPresence);
    uint8_t fall_state = this->hu_.getFallData(this->hu_.eFallState);

    // Update presence binary sensor state
    this->set_presence_(presence == 1);

    // Log data for debugging
    ESP_LOGD(TAG, "Presence: %d, Fall State: %d", presence, fall_state);
  }
}

void DFRobotC1001Component::set_presence_(bool presence) {
  this->presence_ = presence;
#ifdef USE_BINARY_SENSOR
  if (this->presence_binary_sensor_ != nullptr)
    this->presence_binary_sensor_->publish_state(presence);
#endif
}

uint8_t DFRobotC1001Component::read_message_() {
  while (this->available()) {
    uint8_t byte;
    this->read_byte(&byte);

    if (this->read_pos_ == MMWAVE_READ_BUFFER_LENGTH)
      this->read_pos_ = 0;

    if (byte == ASCII_CR)
      continue;
    if (byte >= 0x7F)
      byte = '?';  // Valid UTF-8 string for log functions
    this->read_buffer_[this->read_pos_] = byte;

    if (this->read_pos_ == 9 && byte == '>')
      this->read_buffer_[++this->read_pos_] = ASCII_LF;

    if (this->read_buffer_[this->read_pos_] == ASCII_LF) {
      this->read_buffer_[this->read_pos_] = 0;
      this->read_pos_ = 0;
      ESP_LOGV(TAG, "Message: %s", this->read_buffer_);
      return 1;  // Full message in buffer
    } else {
      this->read_pos_++;
    }
  }
  return 0;  // No full message yet
}

uint8_t DFRobotC1001Component::send_cmd_(const char *cmd, uint32_t duration) {
  // Interval between two commands must be larger than specified duration
  if (millis() - ts_last_cmd_sent_ > duration) {
    this->write_str(cmd);
    ts_last_cmd_sent_ = millis();
    return 1;  // Command sent
  }
  return 0;
}

int8_t CircularCommandQueue::enqueue(std::unique_ptr<Command> cmd) {
  if (this->is_full()) {
    ESP_LOGE(TAG, "Command queue is full");
    return -1;
  } else if (this->is_empty())
    front_++;
  rear_ = (rear_ + 1) % COMMAND_QUEUE_SIZE;
  commands_[rear_] = std::move(cmd);
  return 1;
}

std::unique_ptr<Command> CircularCommandQueue::dequeue() {
  if (this->is_empty())
    return nullptr;
  std::unique_ptr<Command> dequeued_cmd = std::move(commands_[front_]);
  if (front_ == rear_) {
    front_ = -1;
    rear_ = -1;
  } else
    front_ = (front_ + 1) % COMMAND_QUEUE_SIZE;
  return dequeued_cmd;
}

bool CircularCommandQueue::is_empty() { return front_ == -1; }

bool CircularCommandQueue::is_full() { return (rear_ + 1) % COMMAND_QUEUE_SIZE == front_; }

uint8_t CircularCommandQueue::process(DFRobotC1001Component *parent) {
  if (!is_empty()) {
    return commands_[front_]->execute(parent);
  } else {
    return 1;
  }
}

}  // namespace dfrobot_c1001
}  // namespace esphome
