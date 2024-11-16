import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import CONF_ID, UNIT_EMPTY, UNIT_METER, ICON_EMPTY

DEPENDENCIES = ["uart"]

dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
DFRobotC1001 = dfrobot_c1001_ns.class_("DFRobotC1001", cg.PollingComponent, uart.UARTDevice)

CONF_PRESENCE = "presence"
CONF_DISTANCE = "distance"

SENSOR_SCHEMA = sensor.sensor_schema(
    unit_of_measurement=UNIT_EMPTY, accuracy_decimals=0, icon=ICON_EMPTY
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(DFRobotC1001),
        cv.Optional(CONF_PRESENCE): SENSOR_SCHEMA,
        cv.Optional(CONF_DISTANCE): SENSOR_SCHEMA,
    }
).extend(cv.COMPONENT_SCHEMA).extend(uart.UART_DEVICE_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    if CONF_PRESENCE in config:
        presence_sensor = await sensor.new_sensor(config[CONF_PRESENCE])
        cg.add(var.set_presence_sensor(presence_sensor))

    if CONF_DISTANCE in config:
        distance_sensor = await sensor.new_sensor(config[CONF_DISTANCE])
        cg.add(var.set_distance_sensor(distance_sensor))
