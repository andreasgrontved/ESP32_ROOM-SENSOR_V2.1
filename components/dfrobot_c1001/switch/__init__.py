import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import ENTITY_CATEGORY_CONFIG, CONF_TYPE

from .. import CONF_DFROBOT_C1001_ID, DFRobotC1001Component

DEPENDENCIES = ["dfrobot_c1001"]

dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
DFRobotC1001Switch = dfrobot_c1001_ns.class_(
    "DFRobotC1001Switch",
    switch.Switch,
    cg.Component,
    cg.Parented.template(DFRobotC1001Component),
)

C1001PowerSwitch = dfrobot_c1001_ns.class_("C1001PowerSwitch", DFRobotC1001Switch)
C1001LedSwitch = dfrobot_c1001_ns.class_("C1001LedSwitch", DFRobotC1001Switch)
C1001UartPresenceSwitch = dfrobot_c1001_ns.class_(
    "C1001UartPresenceSwitch", DFRobotC1001Switch
)
C1001StartAfterBootSwitch = dfrobot_c1001_ns.class_(
    "C1001StartAfterBootSwitch", DFRobotC1001Switch
)

_SWITCH_SCHEMA = (
    switch.switch_schema(
        entity_category=ENTITY_CATEGORY_CONFIG,
    )
    .extend(
        {
            cv.GenerateID(CONF_DFROBOT_C1001_ID): cv.use_id(DFRobotC1001Component),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)

CONFIG_SCHEMA = cv.typed_schema(
    {
        "sensor_active": _SWITCH_SCHEMA.extend(
            {cv.GenerateID(): cv.declare_id(C1001PowerSwitch)}
        ),
        "turn_on_led": _SWITCH_SCHEMA.extend(
            {cv.GenerateID(): cv.declare_id(C1001LedSwitch)}
        ),
        "presence_via_uart": _SWITCH_SCHEMA.extend(
            {cv.GenerateID(): cv.declare_id(C1001UartPresenceSwitch)}
        ),
        "start_after_boot": _SWITCH_SCHEMA.extend(
            {cv.GenerateID(): cv.declare_id(C1001StartAfterBootSwitch)}
        ),
    }
)


async def to_code(config):
    parent = await cg.get_variable(config[CONF_DFROBOT_C1001_ID])
    var = await switch.new_switch(config)
    await cg.register_component(var, config)
    await cg.register_parented(var, parent)
    cg.add(getattr(parent, f"set_{config[CONF_TYPE]}_switch")(var))
