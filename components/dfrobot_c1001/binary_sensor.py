import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from esphome.const import DEVICE_CLASS_MOTION
from . import CONF_DFROBOT_C1001_ID, DFRobotC1001Component

DEPENDENCIES = ["dfrobot_c1001"]

CONFIG_SCHEMA = binary_sensor.binary_sensor_schema(
    device_class=DEVICE_CLASS_MOTION
).extend(
    {
        cv.GenerateID(CONF_DFROBOT_C1001_ID): cv.use_id(DFRobotC1001Component),
    }
)

async def to_code(config):
    parent = await cg.get_variable(config[CONF_DFROBOT_C1001_ID])
    binary_sens = await binary_sensor.new_binary_sensor(config)

    cg.add(parent.set_detected_binary_sensor(binary_sens))
