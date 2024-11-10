import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.components import uart
from esphome.const import CONF_ID, CONF_HEIGHT, CONF_SENSITIVITY

# Define CONF_FALL_TIME here
CONF_FALL_TIME = "fall_time"

dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
DFRobotC1001Component = dfrobot_c1001_ns.class_("DFRobotC1001Component", cg.Component)

DEPENDENCIES = ["uart"]
CODEOWNERS = ["@andreasgrontved"]

CONF_DFROBOT_C1001_ID = "dfrobot_c1001_id"

CONFIG_SCHEMA = (
    cv.Schema({
        cv.GenerateID(): cv.declare_id(DFRobotC1001Component),
        cv.Optional(CONF_HEIGHT, default=270): cv.int_,
        cv.Optional(CONF_FALL_TIME, default=5): cv.int_,
        cv.Optional(CONF_SENSITIVITY, default=3): cv.int_range(min=0, max=3),
    })
    .extend(uart.UART_DEVICE_SCHEMA)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    cg.add(var.set_installation_height(config[CONF_HEIGHT]))
    cg.add(var.set_fall_time(config[CONF_FALL_TIME]))
    cg.add(var.set_sensitivity(config[CONF_SENSITIVITY]))
