import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import CONF_ID, UNIT_EMPTY, ICON_EMPTY, DEVICE_CLASS_EMPTY

DEPENDENCIES = ["uart"]

dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
dfrobot_c1001 = dfrobot_c1001_ns.class_(
    "dfrobot_c1001", cg.Component, uart.UARTDevice
)

CONFIG_SCHEMA = (
    cv.Schema({cv.GenerateID(): cv.declare_id(dfrobot_c1001),
    cv.Optional("presence"): sensor.sensor_schema(
        unit_of_measurement=UNIT_EMPTY,
        icon=ICON_EMPTY,
        accuracy_decimals=0,
        device_class=DEVICE_CLASS_EMPTY,
        ),
    cv.Optional("movement"): sensor.sensor_schema(
        unit_of_measurement=UNIT_EMPTY,
        icon=ICON_EMPTY,
        accuracy_decimals=0,
        device_class=DEVICE_CLASS_EMPTY,
        ),
    cv.Optional("moving_range"): sensor.sensor_schema(
        unit_of_measurement=UNIT_EMPTY,
        icon=ICON_EMPTY,
        accuracy_decimals=0,
        device_class=DEVICE_CLASS_EMPTY,
        ),
    cv.Optional("breathe_value"): sensor.sensor_schema(
        unit_of_measurement=UNIT_EMPTY,
        icon=ICON_EMPTY,
        accuracy_decimals=0,
        device_class=DEVICE_CLASS_EMPTY,
        ),
    cv.Optional("heart_rate"): sensor.sensor_schema(
        unit_of_measurement=UNIT_EMPTY,
        icon=ICON_EMPTY,
        accuracy_decimals=0,
        device_class=DEVICE_CLASS_EMPTY,
        ),
     })
    .extend(cv.COMPONENT_SCHEMA)
    .extend(uart.UART_DEVICE_SCHEMA)
    
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    if "presence" in config:
        sens = await sensor.new_sensor(config["presence"])
        cg.add(var.set_presence_sensor(sens))
    if "movement" in config:
        sens = await sensor.new_sensor(config["movement"])
        cg.add(var.set_movement_sensor(sens))
    if "moving_range" in config:
        sens = await sensor.new_sensor(config["moving_range"])
        cg.add(var.set_moving_range_sensor(sens))
    if "breathe_value" in config:
        sens = await sensor.new_sensor(config["breathe_value"])
        cg.add(var.set_breathe_value_sensor(sens))
    if "heart_rate" in config:
        sens = await sensor.new_sensor(config["heart_rate"])
        cg.add(var.set_heart_rate_sensor(sens))