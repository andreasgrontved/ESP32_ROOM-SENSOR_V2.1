import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import CONF_ID, UNIT_EMPTY, ICON_EMPTY

# Define namespace and class
dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
DFRobotC1001 = dfrobot_c1001_ns.class_("DFRobotC1001", uart.UARTDevice, cg.Component)

# Define sensor configuration keys
CONF_PRESENCE_SENSOR = "presence_sensor"
CONF_MOTION_SENSOR = "motion_sensor"
CONF_MOVEMENT_PARAM_SENSOR = "movement_param_sensor"
CONF_RESPIRATION_RATE_SENSOR = "respiration_rate_sensor"
CONF_HEART_RATE_SENSOR = "heart_rate_sensor"

# Define the dfrobot_c1001 component schema
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(DFRobotC1001),
    cv.Optional(CONF_PRESENCE_SENSOR): sensor.sensor_schema(UNIT_EMPTY, ICON_EMPTY, 1),
    cv.Optional(CONF_MOTION_SENSOR): sensor.sensor_schema(UNIT_EMPTY, ICON_EMPTY, 1),
    cv.Optional(CONF_MOVEMENT_PARAM_SENSOR): sensor.sensor_schema(UNIT_EMPTY, ICON_EMPTY, 1),
    cv.Optional(CONF_RESPIRATION_RATE_SENSOR): sensor.sensor_schema("breaths/min", ICON_EMPTY, 1),
    cv.Optional(CONF_HEART_RATE_SENSOR): sensor.sensor_schema("beats/min", ICON_EMPTY, 1),
}).extend(uart.UART_DEVICE_SCHEMA)

# Register the component with ESPHome
CONFIG_FILENAME = "dfrobot_c1001"  # Ensure this matches the YAML name

async def to_code(config):
    # Create the component instance
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    # Register sensors explicitly
    if CONF_PRESENCE_SENSOR in config:
        sens = await sensor.new_sensor(config[CONF_PRESENCE_SENSOR])
        cg.add(var.set_presence_sensor(sens))

    if CONF_MOTION_SENSOR in config:
        sens = await sensor.new_sensor(config[CONF_MOTION_SENSOR])
        cg.add(var.set_motion_sensor(sens))

    if CONF_MOVEMENT_PARAM_SENSOR in config:
        sens = await sensor.new_sensor(config[CONF_MOVEMENT_PARAM_SENSOR])
        cg.add(var.set_movement_param_sensor(sens))

    if CONF_RESPIRATION_RATE_SENSOR in config:
        sens = await sensor.new_sensor(config[CONF_RESPIRATION_RATE_SENSOR])
        cg.add(var.set_respiration_rate_sensor(sens))

    if CONF_HEART_RATE_SENSOR in config:
        sens = await sensor.new_sensor(config[CONF_HEART_RATE_SENSOR])
        cg.add(var.set_heart_rate_sensor(sens))
