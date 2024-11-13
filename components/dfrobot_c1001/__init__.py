import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import CONF_ID

# Define namespace
dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
DFRobotC1001 = dfrobot_c1001_ns.class_("DFRobotC1001", cg.Component, uart.UARTDevice)

# Configuration options for each sub-sensor
CONF_PRESENCE_SENSOR = "presence_sensor"
CONF_MOVEMENT_SENSOR = "movement_sensor"
CONF_MOVEMENT_PARAM_SENSOR = "movement_param_sensor"
CONF_RESPIRATION_RATE_SENSOR = "respiration_rate_sensor"
CONF_HEART_RATE_SENSOR = "heart_rate_sensor"

CONFIG_SCHEMA = (
    cv.Schema({
        cv.GenerateID(): cv.declare_id(DFRobotC1001),
        cv.Optional(CONF_PRESENCE_SENSOR): sensor.sensor_schema(),
        cv.Optional(CONF_MOVEMENT_SENSOR): sensor.sensor_schema(),
        cv.Optional(CONF_MOVEMENT_PARAM_SENSOR): sensor.sensor_schema(),
        cv.Optional(CONF_RESPIRATION_RATE_SENSOR): sensor.sensor_schema(),
        cv.Optional(CONF_HEART_RATE_SENSOR): sensor.sensor_schema(),
    })
    .extend(cv.COMPONENT_SCHEMA)
    .extend(uart.UART_DEVICE_SCHEMA)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    # Initialize each optional sub-sensor
    if CONF_PRESENCE_SENSOR in config:
        sens = await sensor.new_sensor(config[CONF_PRESENCE_SENSOR])
        cg.add(var.set_presence_sensor(sens))

    if CONF_MOVEMENT_SENSOR in config:
        sens = await sensor.new_sensor(config[CONF_MOVEMENT_SENSOR])
        cg.add(var.set_movement_sensor(sens))

    if CONF_MOVEMENT_PARAM_SENSOR in config:
        sens = await sensor.new_sensor(config[CONF_MOVEMENT_PARAM_SENSOR])
        cg.add(var.set_movement_param_sensor(sens))

    if CONF_RESPIRATION_RATE_SENSOR in config:
        sens = await sensor.new_sensor(config[CONF_RESPIRATION_RATE_SENSOR])
        cg.add(var.set_respiration_rate_sensor(sens))

    if CONF_HEART_RATE_SENSOR in config:
        sens = await sensor.new_sensor(config[CONF_HEART_RATE_SENSOR])
        cg.add(var.set_heart_rate_sensor(sens))
