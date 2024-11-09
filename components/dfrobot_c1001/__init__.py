import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import CONF_ID
from esphome.const import CONF_ID, CONF_HEIGHT, CONF_SENSITIVITY, CONF_FALL_TIME


DEPENDENCIES = ["uart"]

dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
DFRobotC1001 = dfrobot_c1001_ns.class_(
    "DFRobotC1001", cg.Component, uart.UARTDevice
)

CONFIG_SCHEMA = (
    cv.Schema({
        cv.GenerateID(): cv.declare_id(DFRobotC1001),
        cv.Optional(CONF_HEIGHT, default=270): cv.int_,
        cv.Optional(CONF_SENSITIVITY, default=3): cv.int_,
        cv.Optional(CONF_FALL_TIME, default=5): cv.int_,
    })
    .extend(cv.COMPONENT_SCHEMA)
    .extend(uart.UART_DEVICE_SCHEMA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    cg.add(var.set_installation_height(config[CONF_HEIGHT]))
    cg.add(var.set_fall_sensitivity(config[CONF_SENSITIVITY]))
    cg.add(var.set_fall_time(config[CONF_FALL_TIME]))



from esphome.const import CONF_ID, CONF_HEIGHT, CONF_SENSITIVITY, CONF_FALL_TIME



