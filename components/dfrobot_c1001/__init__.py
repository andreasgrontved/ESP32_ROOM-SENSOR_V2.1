import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.const import CONF_ID

# Define the C++ namespace
dfrobot_ns = cg.esphome_ns.namespace('dfrobot_c1001')
DFRobotHumanDetection = dfrobot_ns.class_('DFRobot_HumanDetection', cg.Component)

# Configuration schema
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(DFRobotHumanDetection),
    cv.Required("rx_pin"): pins.gpio_input_pin_schema,
    cv.Required("tx_pin"): pins.gpio_output_pin_schema,
}).extend(cv.COMPONENT_SCHEMA)

# Code generation logic
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    rx_pin = await cg.gpio_pin_expression(config["rx_pin"])
    tx_pin = await cg.gpio_pin_expression(config["tx_pin"])
    cg.add(var.set_uart_pins(rx_pin, tx_pin))
