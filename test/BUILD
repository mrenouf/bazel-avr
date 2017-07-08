load("@avr_tools//avr_gcc:hex.bzl", "hex", "eeprom", "listing")

cc_binary (
    name = "app",
    copts = ["-mmcu=$(MCU)"],
    linkopts = ["-mmcu=$(MCU)"],
    srcs = ["main.c"],
)

hex(
    name = "hex",
    src = ":app",

)

eeprom(
    name = "eeprom",
    src = ":app",

)

listing(
    name = "listing",
    src = ":app",
)

#genrule (
#    name = "flash",
#    srcs = [":hex"],
#    outs = [ "avrdude.log" ],
#    cmd = "avrdude -p $(MCU) -P $(COM) -c $(PROGR) -U flash:w:$(location :hex) -l $@",
#    local = 1,
#)
