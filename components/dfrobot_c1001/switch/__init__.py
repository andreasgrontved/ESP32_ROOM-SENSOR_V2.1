import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import ENTITY_CATEGORY_CONFIG
from .. import CONF_DFROBOT_C1001_ID, DFRobotC1001Component

DEPENDENCIES = ["dfrobot_c1001"]

dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
DfrobotC1001Switch = dfrobot_c1001_ns.class_("DfrobotC1001Switch", switch.Switch, cg.Component, cg.Parented.template(DFRobotC1001Component))

# Define specific switch types
SenC1001PowerSwitch = dfrobot_c1001_ns.class_("SenC1001PowerSwitch", DfrobotC1001Switch)
SenC1001LedSwitch = dfrobot_c1001_ns.class_("SenC1001LedSwitch", DfrobotC1001Switch)

# Define schema for each switch type
_SWITCH_SCHEMA = (
    switch.switch_schema(entity_category=ENTITY_CATEGORY_CONFIG)
    .extend(
        {
            cv.GenerateID(CONF_DFROBOT_C1001_ID): cv.use_id(DFRobotC1001Component),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.Optional("sensor_active"): _SWITCH_SCHEMA.extend(
            {cv.GenerateID(): cv.declare_id(SenC1001PowerSwitch)}
        ),
        cv.Optional("turn_on_led"): _SWITCH_SCHEMA.extend(
            {cv.GenerateID(): cv.declare_id(SenC1001LedSwitch)}
        ),
    }
)


async def to_code(config):
    parent = await cg.get_variable(config[CONF_DFROBOT_C1001_ID])
    
    for key, switch_type in [("sensor_active", SenC1001PowerSwitch), ("turn_on_led", SenC1001LedSwitch)]:
        if key in config:
            var = await switch.new_switch(config[key])
            await cg.register_component(var, config[key])
            await cg.register_parented(var, parent)
            cg.add(getattr(parent, f"set_{key}_switch")(var))
