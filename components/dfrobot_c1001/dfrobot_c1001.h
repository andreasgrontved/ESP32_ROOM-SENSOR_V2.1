#include "esphome.h"
#include "DFRobot_HumanDetection.h"

namespace esphome {
namespace dfrobot_c1001 {

class DFRobotC1001 : public PollingComponent, public Sensor {
 public:
  void setup() override;
  void update() override;
  void init();

 private:
  DFRobot_HumanDetection hu;
};

}  // namespace dfrobot_c1001
}  // namespace esphome