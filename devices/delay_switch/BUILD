load("@avr_tools//tools/avr:hex.bzl", "hex", "eeprom", "listing")


# Written for Adafruit Trinket (ATTiny 85)
# 
# Functions:
#
# 1. Idle state: output off
# 2. begin idle timer
# 3. Input pin goes active:
#      a. if idle timer > X
#         delay for x seconds
#      b. disable idle timer
#      c. enable output pin
#      d. enable and reset shutdown timer
# 4. When shutdown timer expires, output is disabled
#

config_setting(
    name = "avr",
    values = {
        "cpu": "avr",
    },
)

cc_binary(
    name = "delay_switch",
    srcs = ["delay_switch.c"],
    copts = select({
        ":avr": ["-mmcu=$(MCU)"],
        "//conditions:default": [],
    }),
    linkopts = select({
        ":avr": ["-mmcu=$(MCU)"],
        "//conditions:default": [],
    }),
)

listing(
        name = "delay_switch_listing", 
        src = ":delay_switch"
)

