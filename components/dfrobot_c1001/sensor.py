
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import CONF_ID, CONF_NAME, UNIT_NONE, ICON_EMPTY

DEPENDENCIES = ["uart"]

dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
DFRobotC1001 = dfrobot_c1001_ns.class_("DFRobotC1001Component", cg.PollingComponent, uart.UARTDevice)

CONF_PRESENCE = "presence_sensor"
CONF_MOTION = "motion_sensor"
CONF_DISTANCE = "distance_sensor"
CONF_ENERGY = "energy_sensor"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(DFRobotC1001),
        cv.Optional(CONF_PRESENCE): sensor.sensor_schema(
            unit_of_measurement=UNIT_NONE, icon=ICON_EMPTY, accuracy_decimals=0
        ),
        cv.Optional(CONF_MOTION): sensor.sensor_schema(
            unit_of_measurement=UNIT_NONE, icon=ICON_EMPTY, accuracy_decimals=0
        ),
        cv.Optional(CONF_DISTANCE): sensor.sensor_schema(
            unit_of_measurement="cm", icon=ICON_EMPTY, accuracy_decimals=0
        ),
        cv.Optional(CONF_ENERGY): sensor.sensor_schema(
            unit_of_measurement=UNIT_NONE, icon=ICON_EMPTY, accuracy_decimals=0
        ),
    }
).extend(cv.polling_component_schema("1s")).extend(uart.UART_DEVICE_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    if CONF_PRESENCE in config:
        sens = await sensor.new_sensor(config[CONF_PRESENCE])
        cg.add(var.set_presence_sensor(sens))
    if CONF_MOTION in config:
        sens = await sensor.new_sensor(config[CONF_MOTION])
        cg.add(var.set_motion_sensor(sens))
    if CONF_DISTANCE in config:
        sens = await sensor.new_sensor(config[CONF_DISTANCE])
        cg.add(var.set_distance_sensor(sens))
    if CONF_ENERGY in config:
        sens = await sensor.new_sensor(config[CONF_ENERGY])
        cg.add(var.set_energy_sensor(sens))
