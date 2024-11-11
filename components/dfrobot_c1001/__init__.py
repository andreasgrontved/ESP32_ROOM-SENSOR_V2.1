import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.components import binary_sensor
from esphome.const import CONF_ID

DEPENDENCIES = ["uart"]

dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
DFRobotC1001 = dfrobot_c1001_ns.class_(
    "DFRobotC1001", cg.Component, uart.UARTDevice
)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(DFRobotC1001),
}).extend(cv.COMPONENT_SCHEMA).extend(uart.UART_DEVICE_SCHEMA)

async def to_code(config):
    uart_component = await cg.get_variable(config[uart.CONF_UART_ID])
    var = cg.new_Pvariable(config[CONF_ID], uart_component)
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

