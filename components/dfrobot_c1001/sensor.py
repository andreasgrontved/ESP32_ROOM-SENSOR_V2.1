import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import ICON_EMPTY, UNIT_EMPTY, CONF_ID

DEPENDENCIES = ["uart"]

# Define the namespace and the sensor class
dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
DFRobotC1001Sensor = dfrobot_c1001_ns.class_(
    "DFRobotC1001Sensor", cg.PollingComponent, uart.UARTDevice
)

# Define the configuration schema
CONFIG_SCHEMA = (
    sensor.sensor_schema(
        DFRobotC1001Sensor,
        unit_of_measurement=UNIT_EMPTY,
        icon=ICON_EMPTY,
        accuracy_decimals=1,
    )
    .extend(cv.polling_component_schema("60s"))
    .extend(uart.UART_DEVICE_SCHEMA)
    .extend({cv.Required(CONF_ID): cv.declare_id(DFRobotC1001Sensor)})
)

# Define the to_code function to initialize the sensor
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], DFRobotC1001Sensor)
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
    await sensor.register_sensor(var, config)
