import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.const import CONF_ID

# Define the C++ namespace
dfrobot_ns = cg.esphome_ns.namespace('dfrobot_c1001')
DFRobotHumanDetection = dfrobot_ns.class_('DFRobot_HumanDetection', cg.Component)

# Define configuration parameters
CONF_RX_PIN = "rx_pin"
CONF_TX_PIN = "tx_pin"

# Configuration schema
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(DFRobotHumanDetection),
    cv.Required(CONF_RX_PIN): pins.gpio_input_pin_schema,
    cv.Required(CONF_TX_PIN): pins.gpio_output_pin_schema,
}).extend(cv.COMPONENT_SCHEMA)

# Code generation logic
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    rx_pin = await cg.gpio_pin_expression(config[CONF_RX_PIN])
    tx_pin = await cg.gpio_pin_expression(config[CONF_TX_PIN])
    cg.add(var.set_uart_pins(rx_pin, tx_pin))
