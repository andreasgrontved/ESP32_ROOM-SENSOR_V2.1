import esphome.codegen as cg
from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import (
    DEVICE_CLASS_DISTANCE,
    UNIT_METER,
    UNIT_NONE,
    ICON_EMPTY,
)

from . import CONF_DFROBOT_C1001_ID, DFRobotC1001Component

CONF_PRESENCE_SENSOR = "presence_sensor"
CONF_MOTION_SENSOR = "motion_sensor"
CONF_DISTANCE_SENSOR = "distance_sensor"
CONF_ENERGY_SENSOR = "energy_sensor"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_DFROBOT_C1001_ID): cv.use_id(DFRobotC1001Component),
        cv.Optional(CONF_PRESENCE_SENSOR): sensor.sensor_schema(
            unit_of_measurement=UNIT_NONE,
            icon="mdi:human-greeting",
            accuracy_decimals=0
        ),
        cv.Optional(CONF_MOTION_SENSOR): sensor.sensor_schema(
            unit_of_measurement=UNIT_NONE,
            icon="mdi:run",
            accuracy_decimals=0
        ),
        cv.Optional(CONF_DISTANCE_SENSOR): sensor.sensor_schema(
            device_class=DEVICE_CLASS_DISTANCE,
            unit_of_measurement=UNIT_METER,
            accuracy_decimals=2,
            icon="mdi:signal-distance-variant"
        ),
        cv.Optional(CONF_ENERGY_SENSOR): sensor.sensor_schema(
            unit_of_measurement=UNIT_NONE,
            icon=ICON_EMPTY,
            accuracy_decimals=0
        ),
    }
).extend(cv.polling_component_schema("1s")).extend(uart.UART_DEVICE_SCHEMA)

async def to_code(config):
    component = await cg.get_variable(config[CONF_DFROBOT_C1001_ID])
    if CONF_PRESENCE_SENSOR in config:
        sens = await sensor.new_sensor(config[CONF_PRESENCE_SENSOR])
        cg.add(component.set_presence_sensor(sens))
    if CONF_MOTION_SENSOR in config:
        sens = await sensor.new_sensor(config[CONF_MOTION_SENSOR])
        cg.add(component.set_motion_sensor(sens))
    if CONF_DISTANCE_SENSOR in config:
        sens = await sensor.new_sensor(config[CONF_DISTANCE_SENSOR])
        cg.add(component.set_distance_sensor(sens))
    if CONF_ENERGY_SENSOR in config:
        sens = await sensor.new_sensor(config[CONF_ENERGY_SENSOR])
        cg.add(component.set_energy_sensor(sens))
