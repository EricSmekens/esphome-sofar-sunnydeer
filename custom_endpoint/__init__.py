import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID

custom_endpoint_ns = cg.esphome_ns.namespace("custom_endpoint")

CustomEndpointComponent = custom_endpoint_ns.class_(
    "CustomEndpointComponent",
    cg.Component
)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(CustomEndpointComponent),
    cv.Required("sensorPower"): cv.use_id(sensor.Sensor),
    cv.Optional("sensorVoltage"): cv.use_id(sensor.Sensor),
    cv.Optional("sensorCurrent"): cv.use_id(sensor.Sensor),
    cv.Optional("sensorTotalPower"): cv.use_id(sensor.Sensor),
}).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])

    sensorPower = await cg.get_variable(config["sensorPower"])
    sensorVoltage = await cg.get_variable(config["sensorVoltage"])
    sensorCurrent = await cg.get_variable(config["sensorCurrent"])
    sensorTotalPower = await cg.get_variable(config["sensorTotalPower"])

    cg.add(var.set_act_power(sensorPower, sensorVoltage, sensorCurrent, sensorTotalPower))

    await cg.register_component(var, config)