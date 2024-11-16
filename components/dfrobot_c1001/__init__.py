import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID

dfrobot_c1001_ns = cg.esphome_ns.namespace('dfrobot_c1001')
DFRobotC1001 = dfrobot_c1001_ns.class_('DFRobotC1001', sensor.Sensor)

CONFIG_SCHEMA = sensor.SENSOR_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(DFRobotC1001),
})

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    cg.add(var.init())