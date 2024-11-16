import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import CONF_ID

DEPENDENCIES = ["uart"]

dfrobot_c1001_ns = cg.esphome_ns.namespace('dfrobot_c1001')
DFRobotC1001 = dfrobot_c1001_ns.class_('DFRobotC1001', cg.PollingComponent, uart.UARTDevice)

SENSOR_SCHEMA = sensor.sensor_schema(
    unit_of_measurement="",
    accuracy_decimals=0,
    device_class="",
)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(DFRobotC1001),
    cv.Optional("presence"): SENSOR_SCHEMA,
    cv.Optional("distance"): SENSOR_SCHEMA,
}).extend(cv.COMPONENT_SCHEMA).extend(uart.UART_DEVICE_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
    if "presence" in config:
        sens = await sensor.new_sensor(config["presence"])
        cg.add(var.set_presence_sensor(sens))
    if "distance" in config:
        sens = await sensor.new_sensor(config["distance"])
        cg.add(var.set_distance_sensor(sens))
