#pragma once

#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

namespace esphome {
namespace dfrobot_c1001 {

static const char *const TAG = "dfrobot_c1001.component";

#define TIME_OUT 5000  // 5 seconds

// Command parsing states
#define CMD_HEAD 0
#define CMD_CONFIG 1
#define CMD_CMD 2
#define CMD_LEN_H 3
#define CMD_LEN_L 4
#define CMD_END_H 5
#define CMD_END_L 6
#define CMD_WHITE 7
#define CMD_DATA 8

// Sleep composite state data
typedef struct {
  uint8_t presence;           ///< Presence state
  uint8_t sleepState;         ///< Sleep state
  uint8_t averageRespiration; ///< Average respiration
  uint8_t averageHeartbeat;   ///< Average heartbeat
  uint8_t turnoverNumber;     ///< Turnover number
  uint8_t largeBodyMove;      ///< Large body movement percentage
  uint8_t minorBodyMove;      ///< Minor body movement percentage
  uint8_t apneaEvents;        ///< Apnea events
} sSleepComposite;

// Sleep statistics query
typedef struct {
  uint8_t sleepQualityScore;      ///< Sleep quality score
  uint16_t sleepTime;             ///< Sleep duration in minutes
  uint8_t wakeDuration;           ///< Wake duration
  uint8_t shallowSleepPercentage; ///< Shallow sleep duration percentage
  uint8_t deepSleepPercentage;    ///< Deep sleep duration percentage
  uint8_t timeOutOfBed;           ///< Time out of bed
  uint8_t exitCount;              ///< Exit count
  uint8_t turnOverCount;          ///< Turnover count
  uint8_t averageRespiration;     ///< Average respiration
  uint8_t averageHeartbeat;       ///< Average heartbeat
  uint8_t apneaEvents;            ///< Apnea events
} sSleepStatistics;

class DFRobotC1001 : public uart::UARTDevice, public Component {
 public:
  // Enumerations and typedefs
  typedef enum {
    eSleepMode = 0x02,
    eFallingMode = 0x01,
  } eWorkMode;

  typedef enum {
    eFALLLed = 0x03,
    eHPLed = 0x04,
  } eLed;

  typedef enum {
    eHumanPresence,    ///< Human presence query
    eHumanMovement,    ///< Movement information query
    eHumanMovingRange, ///< Movement distance, range 0~100
    eHumanDistance,
  } esmHuman;
