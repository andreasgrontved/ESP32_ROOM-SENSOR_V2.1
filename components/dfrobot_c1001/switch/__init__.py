import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import ENTITY_CATEGORY_CONFIG, CONF_ID, CONF_NAME

from .. import CONF_DFROBOT_C1001_ID, DFRobotC1001Component

DEPENDENCIES = ["dfrobot_c1001"]

dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
DFRobotC1001Switch = dfrobot_c1001_ns.class_(
    "DFRobotC1001Switch", switch.Switch, cg.Component
)

CONFIG_SCHEMA = (
    switch.SWITCH_SCHEMA.extend(
        {
            cv.GenerateID(): cv.declare_id(DFRobotC1001Switch),
            cv.Required(CONF_NAME): cv.string,
            cv.GenerateID(CONF_DFROBOT_C1001_ID): cv.use_id(DFRobotC1001Component),
        }
    )
)

async def to_code(config):
    var = await switch.new_switch(config)
    await cg.register_component(var, config)
    await cg.register_parented(var, config[CONF_DFROBOT_C1001_ID])
