load("@avr_tools//avr_gcc:hex.bzl", "hex", "eeprom", "listing")

config_setting(
    name = "avr",
    values = {
        "cpu": "avr",
    },
)

cc_library (
    name = "byte_buffer",   
    srcs = ["byte_buffer.c"],
    hdrs = ["byte_buffer.h"],
    copts = select({
        ":avr": ["-mmcu=$(MCU)"],
        "//conditions:default": [],
    }),
    linkopts = select({
        ":avr": ["-mmcu=$(MCU)"],
        "//conditions:default": [],
    }),
)

cc_test(
    name = "byte_buffer_test",
    srcs = ["byte_buffer_test.c"],
    copts = select({
        ":avr": ["-mmcu=$(MCU)"],
        "//conditions:default": [],
    }),
    linkopts = select({
        ":avr": ["-mmcu=$(MCU)"],
        "//conditions:default": [],
    }),
    size = "small",
    deps = [
        ":byte_buffer",
        "//testing/unity:unity_framework",
    ],
)

cc_library (
    name = "ptr_buffer",   
    srcs = ["ptr_buffer.c"],
    hdrs = ["ptr_buffer.h"],
    copts = select({
        ":avr": ["-mmcu=$(MCU)"],
        "//conditions:default": [],
    }),
    linkopts = select({
        ":avr": ["-mmcu=$(MCU)"],
        "//conditions:default": [],
    }),
)

listing(name = "ptr_buffer_listing", src = ":ptr_buffer_test")
 
cc_binary(
    name = "ptr_buffer_test",
    srcs = ["ptr_buffer_test.c"],
    copts = select({
        ":avr": ["-mmcu=$(MCU)"],
        "//conditions:default": [],
    }),
    linkopts = select({
        ":avr": ["-mmcu=$(MCU)"],
        "//conditions:default": [],
    }),
    deps = [
        ":ptr_buffer",
        "//testing/unity:unity_framework",
    ],
)

