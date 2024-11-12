#include "esphome/core/log.h"
#include "dfrobot_c1001.h"

namespace esphome {
namespace dfrobot_c1001 {

DFRobotC1001::DFRobotC1001(uart::UARTComponent *parent) : UARTDevice(parent) {
  this->stream_ = this->get_stream();
}

void DFRobotC1001::setup() {
  ESP_LOGI(TAG, "Initializing DFRobot C1001 sensor...");

  // Initialize the sensor
  uint32_t start_time = millis();
  while (this->begin() != 0) {
    if (millis() - start_time > 10000) {
      ESP_LOGE(TAG, "Sensor initialization failed after 10 seconds.");
      break;
    }
    ESP_LOGW(TAG, "Sensor initialization failed, retrying...");
    delay(1000);
  }

  ESP_LOGI(TAG, "Sensor initialized successfully");

  // Configure the sensor as needed
  if (this->configWorkMode(eSleepMode) != 0) {
    ESP_LOGE(TAG, "Failed to set work mode to Sleep Mode");
  } else {
    ESP_LOGI(TAG, "Work mode set to Sleep Mode");
  }

  // Create and register sensors
  this->presence_binary_sensor_ = new binary_sensor::BinarySensor();
  this->presence_binary_sensor_->set_name("Presence");
  this->presence_binary_sensor_->set_device_class("presence");
  this->register_component(this->presence_binary_sensor_);

  this->motion_sensor_ = new sensor::Sensor();
  this->motion_sensor_->set_name("Motion");
  this->register_component(this->motion_sensor_);

  this->movement_param_sensor_ = new sensor::Sensor();
  this->movement_param_sensor_->set_name("Movement Parameter");
  this->register_component(this->movement_param_sensor_);

  this->respiration_rate_sensor_ = new sensor::Sensor();
  this->respiration_rate_sensor_->set_name("Respiration Rate");
  this->respiration_rate_sensor_->set_unit_of_measurement("breaths/min");
  this->respiration_rate_sensor_->set_icon("mdi:lungs");
  this->register_component(this->respiration_rate_sensor_);

  this->heart_rate_sensor_ = new sensor::Sensor();
  this->heart_rate_sensor_->set_name("Heart Rate");
  this->heart_rate_sensor_->set_unit_of_measurement("bpm");
  this->heart_rate_sensor_->set_icon("mdi:heart-pulse");
  this->register_component(this->heart_rate_sensor_);
}

void DFRobotC1001::loop() {
  // Read and publish presence information
  int presence = this->smHumanData(eHumanPresence);
  if (this->presence_binary_sensor_ != nullptr) {
    this->presence_binary_sensor_->publish_state(presence == 1);
  }

  // Read and publish motion information
  int motion = this->smHumanData(eHumanMovement);
  if (this->motion_sensor_ != nullptr) {
    this->motion_sensor_->publish_state(motion);
  }

  // Read and publish movement parameter
  int movement_param = this->smHumanData(eHumanMovingRange);
  if (this->movement_param_sensor_ != nullptr) {
    this->movement_param_sensor_->publish_state(movement_param);
  }

  // Read and publish respiration rate
  int respiration_rate = this->getBreatheValue();
  if (this->respiration_rate_sensor_ != nullptr) {
    this->respiration_rate_sensor_->publish_state(respiration_rate);
  }

  // Read and publish heart rate
  int heart_rate = this->getHeartRate();
  if (this->heart_rate_sensor_ != nullptr) {
    this->heart_rate_sensor_->publish_state(heart_rate);
  }

  // Log the data
  ESP_LOGD(TAG, "Presence: %d, Motion: %d, Movement Param: %d, Respiration Rate: %d, Heart Rate: %d",
           presence, motion, movement_param, respiration_rate, heart_rate);
}

void DFRobotC1001::dump_config() {
  ESP_LOGCONFIG(TAG, "DFRobot C1001 Sensor:");
  LOG_UART_DEVICE(this);

  if (this->presence_binary_sensor_) {
    LOG_BINARY_SENSOR("  ", "Presence", this->presence_binary_sensor_);
  }
  if (this->motion_sensor_) {
    LOG_SENSOR("  ", "Motion", this->motion_sensor_);
  }
  if (this->movement_param_sensor_) {
    LOG_SENSOR("  ", "Movement Parameter", this->movement_param_sensor_);
  }
  if (this->respiration_rate_sensor_) {
    LOG_SENSOR("  ", "Respiration Rate", this->respiration_rate_sensor_);
  }
  if (this->heart_rate_sensor_) {
    LOG_SENSOR("  ", "Heart Rate", this->heart_rate_sensor_);
  }
}

// Implementations of the methods from the original library

uint8_t DFRobotC1001::begin(void) {
  uint8_t data = 0x0f;
  uint8_t buf[10];
  if (getData(0x01, 0x83, 1, &data, buf) == 0) {
    return 0;
  }
  return 1;
}

uint8_t DFRobotC1001::configWorkMode(eWorkMode mode) {
  uint8_t data = 0x0f;
  uint8_t buf[10];
  uint8_t cmdBuf[10] = {0x53, 0x59, 0x02, 0x08, 0x00, 0x01, 0x00, 0x00, 0x54, 0x43};

  if (getData(0x02, 0xA8, 1, &data, buf) == 0) {
    if (buf[6] == mode) {
      return 0;
    } else {
      cmdBuf[6] = mode;
      cmdBuf[7] = sumData(7, cmdBuf);
      this->stream_->write(cmdBuf, 10);

      uint32_t start_time = millis();
      while (millis() - start_time < 10000) {  // Wait for mode switch
        // Do nothing, just wait
      }

      if (getData(0x02, 0xA8, 1, &data, buf) == 0) {
        if (buf[6] == mode) {
          return 0;
        } else {
          return 1;
        }
      }
      return 1;
    }
  }
  return 1;
}

uint8_t DFRobotC1001::getWorkMode(void) {
  uint8_t buf[10];
  uint8_t data = 0x0f, ret = 2;
  if (getData(0x02, 0xA8, 1, &data, buf) == 0) {
    ret = buf[6];
  }
  return ret;
}

uint16_t DFRobotC1001::smHumanData(esmHuman hm) {
  uint8_t data = 0x0f;
  uint8_t buf[15];
  uint16_t ret = 0;
  switch (hm) {
    case eHumanPresence:
      if (getData(0x80, 0x81, 1, &data, buf) == 0) {
        ret = buf[6];
      }
      break;
    case eHumanMovement:
      if (getData(0x80, 0x82, 1, &data, buf) == 0) {
        ret = buf[6];
      }
      break;
    case eHumanMovingRange:
      if (getData(0x80, 0x83, 1, &data, buf) == 0) {
        ret = buf[6];
      }
      break;
    case eHumanDistance:
      if (getData(0x80, 0x84, 1, &data, buf) == 0) {
        ret = buf[6] << 8 | buf[7];
      }
      break;
    default:
      break;
  }
  return ret;
}

uint8_t DFRobotC1001::getBreatheValue(void) {
  uint8_t data = 0x0f, ret = 0xff;
  uint8_t buf[15];
  if (getData(0x81, 0x82, 1, &data, buf) == 0) {
    ret = buf[6];
  }
  return ret;
}

uint8_t DFRobotC1001::getHeartRate(void) {
  uint8_t data = 0x0f, ret = 0xff;
  uint8_t buf[15];
  if (getData(0x85, 0x82, 1, &data, buf) == 0) {
    ret = buf[6];
  }
  return ret;
}

uint8_t DFRobotC1001::getData(uint8_t con, uint8_t cmd, uint16_t len, uint8_t *senData, uint8_t *retData) {
  uint32_t timeStart = millis();
  uint32_t timeStart1 = 0;
  uint8_t data = 0, state = CMD_WHITE;
  uint16_t _len = 0;
  uint8_t count = 0;

  uint8_t cmdBuf[20];
  cmdBuf[0] = 0x53;
  cmdBuf[1] = 0x59;
  cmdBuf[2] = con;
  cmdBuf[3] = cmd;
  cmdBuf[4] = (len >> 8) & 0xff;
  cmdBuf[5] = len & 0xff;
  memcpy(&cmdBuf[6], senData, len);
  cmdBuf[6 + len] = sumData(6 + len, cmdBuf);
  cmdBuf[7 + len] = 0x54;
  cmdBuf[8 + len] = 0x43;

  while (true) {
    if ((millis() - timeStart1) > 500) {
      while (this->stream_->available() > 0) {
        this->stream_->read();
      }
      this->stream_->write(cmdBuf, 9 + len);
      timeStart1 = millis();
    }

    if (this->stream_->available() > 0) {
      data = this->stream_->read();
    }

    // Update timeout check
    if ((millis() - timeStart) > TIME_OUT) {
      ESP_LOGE(TAG, "Time out");
      return 2;
    }

    switch (state) {
      case CMD_WHITE:
        if (data == 0x53) {
          retData[0] = data;
          state = CMD_HEAD;
          count = 0;  // Reset count
        }
        break;
      case CMD_HEAD:
        if (data == 0x59) {
          state = CMD_CONFIG;
          retData[1] = data;
        } else {
          state = CMD_WHITE;
        }
        break;
      case CMD_CONFIG:
        if (data == con) {
          state = CMD_CMD;
          retData[2] = data;
        } else {
          state = CMD_WHITE;
        }
        break;
      case CMD_CMD:
        if (data == cmd) {
          state = CMD_LEN_H;
          retData[3] = data;
        } else {
          state = CMD_WHITE;
        }
        break;
      case CMD_LEN_H:
        retData[4] = data;
        _len = data << 8;
        state = CMD_LEN_L;
        break;
      case CMD_LEN_L:
        retData[5] = data;
        _len |= data;
        state = CMD_DATA;
        break;
      case CMD_DATA:
        if (count < _len) {
          retData[6 + count] = data;
          count++;
        } else {
          if (data == sumData(6 + count, retData)) {
            retData[6 + _len] = data;
            state = CMD_END_H;
          } else {
            state = CMD_WHITE;
          }
        }
        break;
      case CMD_END_H:
        retData[7 + _len] = data;
        state = CMD_END_L;
        break;
      case CMD_END_L:
        retData[8 + _len] = data;
        return 0;
      default:
        break;
    }
  }
  return 0;
}

uint8_t DFRobotC1001::sumData(uint8_t len, uint8_t *buf) {
  uint16_t data = 0;
  uint8_t *_buf = buf;
  for (uint8_t i = 0; i < len; i++) {
    data += _buf[i];
  }
  return data & 0xff;
}

}  // namespace dfrobot_c1001
}  // namespace esphome
