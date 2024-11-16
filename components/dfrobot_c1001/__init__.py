import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome import pins

DEPENDENCIES = ['uart']

dfrobot_c1001_ns = cg.esphome_ns.namespace('dfrobot_c1001')
DFRobotC1001 = dfrobot_c1001_ns.class_('DFRobotC1001', uart.UARTDevice, cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(DFRobotC1001),
    cv.Optional('presence_sensor'): sensor.sensor_schema(),
    cv.Optional('movement_sensor'): sensor.sensor_schema(),
    cv.Optional('movement_param_sensor'): sensor.sensor_schema(),
    cv.Optional('respiration_rate_sensor'): sensor.sensor_schema(),
    cv.Optional('heart_rate_sensor'): sensor.sensor_schema(),
}).extend(cv.COMPONENT_SCHEMA).extend(uart.UART_DEVICE_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    if 'presence_sensor' in config:
        sens = yield sensor.new_sensor(config['presence_sensor'])
        cg.add(var.set_presence_sensor(sens))
    if 'movement_sensor' in config:
        sens = yield sensor.new_sensor(config['movement_sensor'])
        cg.add(var.set_movement_sensor(sens))
    if 'movement_param_sensor' in config:
        sens = yield sensor.new_sensor(config['movement_param_sensor'])
        cg.add(var.set_movement_param_sensor(sens))
    if 'respiration_rate_sensor' in config:
        sens = yield sensor.new_sensor(config['respiration_rate_sensor'])
        cg.add(var.set_respiration_rate_sensor(sens))
    if 'heart_rate_sensor' in config:
        sens = yield sensor.new_sensor(config['heart_rate_sensor'])
        cg.add(var.set_heart_rate_sensor(sens))
    yield cg.register_component(var, config)
    yield uart.register_uart_device(var, config)