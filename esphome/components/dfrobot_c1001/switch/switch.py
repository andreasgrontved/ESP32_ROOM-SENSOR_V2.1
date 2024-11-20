
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import CONF_ID, CONF_NAME

DEPENDENCIES = ["dfrobot_c1001"]

dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
DFRobotC1001Switch = dfrobot_c1001_ns.class_("DFRobotC1001Switch", switch.Switch)

CONF_FALL_DETECTION = "fall_detection"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(DFRobotC1001Switch),
        cv.Required(CONF_NAME): cv.string,
    }
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config[CONF_NAME])
    await cg.register_component(var, config)
    await switch.register_switch(var, config)
