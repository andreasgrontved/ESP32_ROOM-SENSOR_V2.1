import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import CONF_ID

DEPENDENCIES = ["uart"]

dfrobot_c1001_ns = cg.esphome_ns.namespace('dfrobot_c1001')
DFRobotC1001 = dfrobot_c1001_ns.class_('DFRobotC1001', cg.PollingComponent, uart.UARTDevice)

CONFIG_SCHEMA = (
    sensor.SENSOR_SCHEMA.extend({
        cv.GenerateID(): cv.declare_id(DFRobotC1001),
    })
    .extend(cv.COMPONENT_SCHEMA)
    .extend(uart.UART_DEVICE_SCHEMA)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)