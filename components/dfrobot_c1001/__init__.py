import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.automation import maybe_simple_id
from esphome.const import CONF_FACTORY_RESET, CONF_ID, CONF_SENSITIVITY, CONF_HEIGHT, CONF_FALL_TIME
from esphome.components import uart

CODEOWNERS = ["@andreasgrontved"]
DEPENDENCIES = ["uart"]
MULTI_CONF = True

dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
DFRobotC1001Component = dfrobot_c1001_ns.class_("DFRobotC1001Component", cg.Component)

# Actions
DFRobotC1001ResetAction = dfrobot_c1001_ns.class_("DFRobotC1001ResetAction", automation.Action)
DFRobotC1001SettingsAction = dfrobot_c1001_ns.class_("DFRobotC1001SettingsAction", automation.Action)

CONF_DFROBOT_C1001_ID = "dfrobot_c1001_id"

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(DFRobotC1001Component),
            cv.Optional(CONF_HEIGHT, default=270): cv.int_,
            cv.Optional(CONF_FALL_TIME, default=5): cv.int_,
            cv.Optional(CONF_SENSITIVITY, default=3): cv.int_range(min=0, max=3),
            cv.Optional(CONF_FACTORY_RESET): cv.boolean,
        }
    ).extend(uart.UART_DEVICE_SCHEMA)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    cg.add(var.set_installation_height(config[CONF_HEIGHT]))
    cg.add(var.set_fall_time(config[CONF_FALL_TIME]))
    cg.add(var.set_sensitivity(config[CONF_SENSITIVITY]))
    if config.get(CONF_FACTORY_RESET):
        cg.add(var.factory_reset())

@automation.register_action(
    "dfrobot_c1001.reset",
    DFRobotC1001ResetAction,
    maybe_simple_id(
        {
            cv.GenerateID(): cv.use_id(DFRobotC1001Component),
        }
    ),
)
async def dfrobot_c1001_reset_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    return var

@automation.register_action(
    "dfrobot_c1001.settings",
    DFRobotC1001SettingsAction,
    cv.Schema(
        {
            cv.GenerateID(): cv.use_id(DFRobotC1001Component),
            cv.Optional(CONF_FACTORY_RESET): cv.templatable(cv.boolean),
            cv.Optional(CONF_HEIGHT): cv.templatable(cv.int_),
            cv.Optional(CONF_FALL_TIME): cv.templatable(cv.int_),
            cv.Optional(CONF_SENSITIVITY): cv.templatable(cv.int_range(min=0, max=3)),
        }
    ),
)
async def dfrobot_c1001_settings_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])

    if CONF_FACTORY_RESET in config:
        template_ = await cg.templatable(config[CONF_FACTORY_RESET], args, bool)
        cg.add(var.set_factory_reset(template_))

    if CONF_HEIGHT in config:
        template_ = await cg.templatable(config[CONF_HEIGHT], args, int)
        cg.add(var.set_installation_height(template_))

    if CONF_FALL_TIME in config:
        template_ = await cg.templatable(config[CONF_FALL_TIME], args, int)
        cg.add(var.set_fall_time(template_))

    if CONF_SENSITIVITY in config:
        template_ = await cg.templatable(config[CONF_SENSITIVITY], args, int)
        cg.add(var.set_sensitivity(template_))

    return var
