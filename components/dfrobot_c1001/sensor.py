import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import ICON_EYE, UNIT_EMPTY

DEPENDENCIES = ["uart"]

# Define the namespace for the component
dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
DFRobotC1001Sensor = dfrobot_c1001_ns.class_(
    "DFRobotC1001Sensor", cg.PollingComponent, uart.UARTDevice
)

# Define the configuration schema
CONFIG_SCHEMA = (
    sensor.sensor_schema(
        DFRobotC1001Sensor,
        unit_of_measurement=UNIT_EMPTY,
        icon=ICON_EYE,
        accuracy_decimals=0,
    )
    .extend(cv.polling_component_schema("1s"))  # Poll every 1 second for presence detection
    .extend(uart.UART_DEVICE_SCHEMA)
)

async def to_code(config):
    # Initialize the sensor
    var = cg.new_Pvariable(DFRobotC1001Sensor)
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)
    await uart.register_uart_device(var, config)
