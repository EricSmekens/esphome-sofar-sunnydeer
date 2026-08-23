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
    cv.Required("sensor"): cv.use_id(sensor.Sensor),
}).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])

    sensor_var = await cg.get_variable(config["sensor"])
    cg.add(var.set_act_power(sensor_var))

    await cg.register_component(var, config)