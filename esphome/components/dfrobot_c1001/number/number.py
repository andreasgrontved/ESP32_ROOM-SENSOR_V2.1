
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import number
from esphome.const import CONF_ID, CONF_NAME, CONF_MIN_VALUE, CONF_MAX_VALUE, CONF_STEP, UNIT_CENTIMETER

DEPENDENCIES = ["dfrobot_c1001"]

dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
DFRobotC1001Number = dfrobot_c1001_ns.class_("DFRobotC1001Number", number.Number)

CONF_INSTALLATION_HEIGHT = "installation_height"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(DFRobotC1001Number),
        cv.Required(CONF_NAME): cv.string,
        cv.Optional(CONF_MIN_VALUE, default=10): cv.float_,
        cv.Optional(CONF_MAX_VALUE, default=500): cv.float_,
        cv.Optional(CONF_STEP, default=1): cv.float_,
    }
)

async def to_code(config):
    var = cg.new_Pvariable(
        config[CONF_ID], config[CONF_NAME], config[CONF_MIN_VALUE], config[CONF_MAX_VALUE], config[CONF_STEP]
    )
    await cg.register_component(var, config)
    await number.register_number(var, config)
