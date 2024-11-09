import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import CONF_ID, ICON_EYE, UNIT_EMPTY

# Define the namespace and class for your component
dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
DFRobotC1001Sensor = dfrobot_c1001_ns.class_("DFRobotC1001Sensor", sensor.Sensor, cg.PollingComponent)

# Configuration schema
CONFIG_SCHEMA = (
    sensor.sensor_schema(DFRobotC1001Sensor, unit_of_measurement=UNIT_EMPTY, icon=ICON_EYE, accuracy_decimals=0)
    .extend(cv.polling_component_schema("60s"))
    .extend(uart.UART_DEVICE_SCHEMA)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config)
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
    await sensor.register_sensor(var, config)
