load("@avr_tools//tools/avr:hex.bzl", "hex", "eeprom", "listing")

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

cc_library (
    name = "ring_buffer_u8",
    srcs = ["ring_buffer_u8.c"],
    hdrs = ["ring_buffer_u8.h"],
    copts = select({
        ":avr": ["-mmcu=$(MCU)"],
        "//conditions:default": ["-DDEBUG"],
    }),
    linkopts = select({
        ":avr": ["-mmcu=$(MCU)"],
        "//conditions:default": [],
    }),
)

cc_test(
    name = "ring_buffer_u8_test",
    srcs = ["ring_buffer_u8_test.c"],
    size = "small",
    deps = [
        ":ring_buffer_u8",
        "//testing/unity:unity_framework",
    ],
)

cc_library (
    name = "ring_buffer_u16",
    srcs = ["ring_buffer_u16.c"],
    hdrs = ["ring_buffer_u16.h"],
    copts = select({
        ":avr": ["-mmcu=$(MCU)"],
        "//conditions:default": ["-DDEBUG"],
    }),
    linkopts = select({
        ":avr": ["-mmcu=$(MCU)"],
        "//conditions:default": [],
    }),
)

cc_test(
    name = "ring_buffer_u16_test",
    srcs = ["ring_buffer_u16_test.c"],
    size = "small",
    deps = [
        ":ring_buffer_u16",
        "//testing/unity:unity_framework",
    ],
)

cc_binary (
    name = "ring_buffer_u8_sample",
    srcs = ["ring_buffer_u8_sample.c"],
    deps = [":ring_buffer_u8"],
    copts = select({
        ":avr": ["-mmcu=$(MCU)"],
        "//conditions:default": [],
    }),
    linkopts = select({
        ":avr": ["-mmcu=$(MCU)"],
        "//conditions:default": [],
    }),
)


cc_binary (
    name = "ring_buffer_u16_sample",
    srcs = ["ring_buffer_u16_sample.c"],
    deps = [":ring_buffer_u16"],
    copts = select({
        ":avr": ["-mmcu=$(MCU)"],
        "//conditions:default": [],
    }),
    linkopts = select({
        ":avr": ["-mmcu=$(MCU)"],
        "//conditions:default": [],
    }),
)


