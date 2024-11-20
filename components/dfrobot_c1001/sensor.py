import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import CONF_ID, UNIT_NONE, ICON_EMPTY, CONF_NAME

DEPENDENCIES = ["uart"]

dfrobot_c1001_ns = cg.esphome_ns.namespace("dfrobot_c1001")
DFRobotC1001 = dfrobot_c1001_ns.class_("DFRobotC1001Component", cg.PollingComponent, uart.UARTDevice)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(DFRobotC1001),
        cv.Optional("presence_sensor"): sensor.sensor_schema(
            unit_of_measurement=UNIT_NONE, icon=ICON_EMPTY, accuracy_decimals=0
        ),
        cv.Optional("motion_sensor"): sensor.sensor_schema(
            unit_of_measurement=UNIT_NONE, icon=ICON_EMPTY, accuracy_decimals=0
        ),
        cv.Optional("distance_sensor"): sensor.sensor_schema(
            unit_of_measurement="cm", icon=ICON_EMPTY, accuracy_decimals=2
        ),
        cv.Optional("energy_sensor"): sensor.sensor_schema(
            unit_of_measurement=UNIT_NONE, icon=ICON_EMPTY, accuracy_decimals=0
        ),
    }
).extend(cv.polling_component_schema("1s")).extend(uart.UART_DEVICE_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    if "presence_sensor" in config:
        sens = await sensor.new_sensor(config["presence_sensor"])
        cg.add(var.set_presence_sensor(sens))
    if "motion_sensor" in config:
        sens = await sensor.new_sensor(config["motion_sensor"])
        cg.add(var.set_motion_sensor(sens))
    if "distance_sensor" in config:
        sens = await sensor.new_sensor(config["distance_sensor"])
        cg.add(var.set_distance_sensor(sens))
    if "energy_sensor" in config:
        sens = await sensor.new_sensor(config["energy_sensor"])
        cg.add(var.set_energy_sensor(sens))
