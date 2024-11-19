import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import CONF_ID, UNIT_EMPTY, ICON_EMPTY

# Define namespace and class
dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
DFRobotC1001 = dfrobot_c1001_ns.class_("DFRobotC1001", uart.UARTDevice, cg.Component)

# Sensor configurations
SENSORS = {
    "presence_sensor": ("Human Presence", UNIT_EMPTY, ICON_EMPTY),
    "motion_sensor": ("Motion Information", UNIT_EMPTY, ICON_EMPTY),
    "movement_param_sensor": ("Body Movement Parameter", UNIT_EMPTY, ICON_EMPTY),
    "respiration_rate_sensor": ("Respiration Rate", "breaths/min", ICON_EMPTY),
    "heart_rate_sensor": ("Heart Rate", "beats/min", ICON_EMPTY),
}

# Configuration schema
CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(DFRobotC1001),
    }
).extend(uart.UART_DEVICE_SCHEMA)

# Code generation logic
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    # Register all sensors
    for key, (name, unit, icon) in SENSORS.items():
        sens = cg.new_Pvariable(getattr(DFRobotC1001, key), var)
        await sensor.register_sensor(sens, name, unit, icon)
