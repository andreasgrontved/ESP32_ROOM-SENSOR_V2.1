import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor, switch, number
from esphome.const import CONF_ID, UNIT_EMPTY, ICON_EMPTY, DEVICE_CLASS_EMPTY

# Define custom constants
CONF_PRESENCE = "presence"
CONF_MOVEMENT = "movement"
CONF_MOVING_RANGE = "moving_range"
CONF_BREATHE_VALUE = "breathe_value"
CONF_HEART_RATE = "heart_rate"
CONF_HEIGHT = "height"
CONF_WORK_MODE = "work_mode"  # Custom constant

DEPENDENCIES = ["uart"]

dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
DFRobotC1001Component = dfrobot_c1001_ns.class_(
    "DFRobotC1001Component", cg.PollingComponent, uart.UARTDevice
)

CONFIG_SCHEMA = (
    cv.Schema({
        cv.GenerateID(): cv.declare_id(DFRobotC1001Component),
        cv.Optional(CONF_PRESENCE): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
        ),
        cv.Optional(CONF_MOVEMENT): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
        ),
        cv.Optional(CONF_MOVING_RANGE): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
        ),
        cv.Optional(CONF_BREATHE_VALUE): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
        ),
        cv.Optional(CONF_HEART_RATE): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
        ),
        cv.Optional(CONF_HEIGHT): number.NUMBER_SCHEMA,
        cv.Optional(CONF_WORK_MODE): switch.SWITCH_SCHEMA,
    })
    .extend(cv.COMPONENT_SCHEMA)
    .extend(uart.UART_DEVICE_SCHEMA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    if CONF_PRESENCE in config:
        sens = await sensor.new_sensor(config[CONF_PRESENCE])
        cg.add(var.set_presence_sensor(sens))
    if CONF_MOVEMENT in config:
        sens = await sensor.new_sensor(config[CONF_MOVEMENT])
        cg.add(var.set_movement_sensor(sens))
    if CONF_MOVING_RANGE in config:
        sens = await sensor.new_sensor(config[CONF_MOVING_RANGE])
        cg.add(var.set_moving_range_sensor(sens))
    if CONF_BREATHE_VALUE in config:
        sens = await sensor.new_sensor(config[CONF_BREATHE_VALUE])
        cg.add(var.set_breathe_value_sensor(sens))
    if CONF_HEART_RATE in config:
        sens = await sensor.new_sensor(config[CONF_HEART_RATE])
        cg.add(var.set_heart_rate_sensor(sens))
    if CONF_HEIGHT in config:
        num = await number.new_number(config[CONF_HEIGHT])
        cg.add(var.set_height_number(num))
    if CONF_WORK_MODE in config:
        sw = await switch.new_switch(config[CONF_WORK_MODE])
        cg.add(var.set_work_mode_switch(sw))
