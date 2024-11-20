
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import select
from esphome.const import CONF_ID, CONF_NAME, CONF_OPTIONS

DEPENDENCIES = ["dfrobot_c1001"]

dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
DFRobotC1001Select = dfrobot_c1001_ns.class_("DFRobotC1001Select", select.Select)

CONF_SLEEP_MODE = "sleep_mode"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(DFRobotC1001Select),
        cv.Required(CONF_NAME): cv.string,
        cv.Required(CONF_OPTIONS): cv.ensure_list(cv.string),
    }
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config[CONF_NAME], config[CONF_OPTIONS])
    await cg.register_component(var, config)
    await select.register_select(var, config)
