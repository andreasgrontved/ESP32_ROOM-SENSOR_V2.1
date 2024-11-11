import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome import pins
from esphome.const import CONF_ID

DEPENDENCIES = ["uart"]

# Define the namespace for your component
dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")

# Define the DFRobotC1001 class within that namespace
DFRobotC1001 = dfrobot_c1001_ns.class_(
    "DFRobotC1001", cg.Component, uart.UARTDevice
)

CONFIG_SCHEMA = (
    cv.Schema({cv.GenerateID(): cv.declare_id(DFRobotC1001)})
    .extend(cv.COMPONENT_SCHEMA)
    .extend(uart.UART_DEVICE_SCHEMA)
)

async def to_code(config):
    # Get the UART component
    uart_component = await cg.get_variable(config[uart.CONF_UART_ID])

    # Create a new instance of your component, passing in the UART component
    var = cg.new_Pvariable(config[CONF_ID], uart_component)

    # Register the component and UART device
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
