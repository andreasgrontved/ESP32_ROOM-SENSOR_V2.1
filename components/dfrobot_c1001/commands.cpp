#include "commands.h"
#include <cmath>
#include "esphome/core/log.h"
#include "dfrobot_c1001.h"

namespace esphome {
namespace dfrobot_c1001 {

static const char *const TAG = "dfrobot_c1001.commands";

uint8_t Command::execute(DFRobotC1001Component *parent) {
  this->parent_ = parent;
  if (this->cmd_sent_) {
    if (this->parent_->read_message_()) {
      std::string message(this->parent_->read_buffer_);
      if (message.rfind("is not recognized as a CLI command") != std::string::npos) {
        ESP_LOGD(TAG, "Command not recognized by sensor");
        if (this->retries_left_ > 0) {
          this->retries_left_ -= 1;
          this->cmd_sent_ = false;
          ESP_LOGD(TAG, "Retrying...");
          return 0;
        } else {
          this->parent_->find_prompt_();
          return 1;  // Command done
        }
      }
      uint8_t rc = on_message(message);
      if (rc == 2) {
        if (this->retries_left_ > 0) {
          this->retries_left_ -= 1;
          this->cmd_sent_ = false;
          ESP_LOGD(TAG, "Retrying...");
          return 0;
        } else {
          this->parent_->find_prompt_();
          return 1;  // Command done
        }
      } else if (rc == 0) {
        return 0;
      } else {
        this->parent_->find_prompt_();
        return 1;
      }
    }
    if (millis() - this->parent_->ts_last_cmd_sent_ > this->timeout_ms_) {
      ESP_LOGD(TAG, "Command timeout");
      if (this->retries_left_ > 0) {
        this->retries_left_ -= 1;
        this->cmd_sent_ = false;
        ESP_LOGD(TAG, "Retrying...");
      } else {
        return 1;  // Command done
      }
    }
  } else if (this->parent_->send_cmd_(this->cmd_.c_str(), this->cmd_duration_ms_)) {
    this->cmd_sent_ = true;
  }
  return 0;  // Command not done yet
}

uint8_t ReadStateCommand::execute(DFRobotC1001Component *parent) {
  this->parent_ = parent;
  if (this->parent_->read_message_()) {
    std::string message(this->parent_->read_buffer_);
    if (message.rfind("$DFBS,0, , , *") != std::string::npos) {
      this->parent_->set_presence_(false);
      this->parent_->set_active(true);
      return 1;  // Command done
    } else if (message.rfind("$DFBS,1, , , *") != std::string::npos) {
      this->parent_->set_presence_(true);
      this->parent_->set_active(true);
      return 1;  // Command done
    }
  }
  if (millis() - this->parent_->ts_last_cmd_sent_ > this->timeout_ms_) {
    return 1;  // Command done, timeout
  }
  return 0;  // Command not done yet.
}

uint8_t ReadStateCommand::on_message(std::string &message) { return 1; }

uint8_t PowerCommand::on_message(std::string &message) {
  if (message == "sensor stopped already") {
    this->parent_->set_active(false);
    ESP_LOGI(TAG, "Stopped sensor (already stopped)");
    return 1;  // Command done
  } else if (message == "sensor started already") {
    this->parent_->set_active(true);
    ESP_LOGI(TAG, "Started sensor (already started)");
    return 1;  // Command done
  } else if (message == "Done") {
    this->parent_->set_active(this->power_on_);
    ESP_LOGI(TAG, this->power_on_ ? "Started sensor" : "Stopped sensor");
    return 1;  // Command done
  }
  return 0;  // Command not done yet.
}

uint8_t SetWorkModeCommand::on_message(std::string &message) {
  if (message == "Done") {
    ESP_LOGI(TAG, "Work mode set to %d", this->mode_);
    return 1;  // Command done
  }
  return 0;  // Command not done yet.
}

uint8_t SetInstallationHeightCommand::on_message(std::string &message) {
  if (message == "Done") {
    ESP_LOGI(TAG, "Installation height set.");
    return 1;  // Command done
  }
  return 0;  // Command not done yet.
}

uint8_t SetFallSensitivityCommand::on_message(std::string &message) {
  if (message == "Done") {
    ESP_LOGI(TAG, "Fall sensitivity set to %d", this->sensitivity_);
    return 1;  // Command done
  }
  return 0;  // Command not done yet.
}

uint8_t LedModeCommand::on_message(std::string &message) {
  if (message == "Done") {
    ESP_LOGI(TAG, this->active_ ? "LED mode on" : "LED mode off");
    this->parent_->set_led_active(this->active_);
    return 1;  // Command done
  }
  return 0;  // Command not done yet
}

uint8_t ResetSystemCommand::on_message(std::string &message) {
  if (message == "reset complete") {
    ESP_LOGI(TAG, "Sensor reset.");
    return 1;  // Command done
  }
  return 0;  // Command not done yet
}

uint8_t SaveConfigurationCommand::on_message(std::string &message) {
  if (message == "no parameter has changed") {
    ESP_LOGI(TAG, "No config change detected, not saving.");
    return 1;  // Command done
  } else if (message == "Done") {
    ESP_LOGI(TAG, "Configuration saved.");
    return 1;  // Command done
  }
  return 0;  // Command not done yet
}

}  // namespace dfrobot_c1001
}  // namespace esphome
