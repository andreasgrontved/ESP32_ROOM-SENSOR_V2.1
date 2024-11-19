from esphome import automation
from esphome.components import uart
from esphome.const import CONF_ID
import esphome.config_validation as cv
import logging

DEPENDENCIES = ["uart"]

_LOGGER = logging.getLogger(__name__)

_LOGGER.info("DFRobot C1001 Component loaded successfully")
