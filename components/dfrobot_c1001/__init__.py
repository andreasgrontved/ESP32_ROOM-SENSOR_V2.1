import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome import automation

# Declare namespace and class
dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
DFRobotC1001 = dfrobot_c1001_ns.class_("DFRobotC1001", uart.UARTDevice, cg.Component)

# Define configuration schema
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(DFRobotC1001),
}).extend(uart.UART_DEVICE_SCHEMA)

# Code generation logic
async def to_code(config):
    # Create an instance of the component
    var = cg.new_Pvariable(config[cv.GenerateID()])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
