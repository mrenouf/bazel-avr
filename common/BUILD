config_setting(
    name = "avr",
    values = {
        "cpu": "avr",
    },
)

cc_library (
    name = "port_macros",
    hdrs = ["port_macros.h"],
    copts = select({
        ":avr": ["-mmcu=$(MCU)"],
        "//conditions:default": [],
    }),
    visibility = ["//visibility:public"],
)

