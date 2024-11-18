import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.automation import maybe_simple_id
from esphome.const import CONF_ID
from esphome.components import uart

# Define namespace and dependencies
dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
DFRobotC1001Component = dfrobot_c1001_ns.class_("DFRobotC1001Component", cg.Component)

CODEOWNERS = ["@yourgithub"]
DEPENDENCIES = ["uart"]
MULTI_CONF = True

CONF_DFROBOT_C1001_ID = "dfrobot_c1001_id"
CONF_PRESENCE = "presence"
CONF_MOVEMENT = "movement"
CONF_MOVING_RANGE = "moving_range"
CONF_BREATHE_VALUE = "breathe_value"
CONF_HEART_RATE = "heart_rate"

# Component schema
CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(DFRobotC1001Component),
        }
    ).extend(uart.UART_DEVICE_SCHEMA)
)

# Action for reset (if needed)
DfrobotC1001ResetAction = dfrobot_c1001_ns.class_(
    "DfrobotC1001ResetAction", automation.Action
)

@automation.register_action(
    "dfrobot_c1001.reset",
    DfrobotC1001ResetAction,
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


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
