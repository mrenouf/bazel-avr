#!/bin/bash


bazel build -c opt --config=trinket :delay_switch_hex
avrdude -C avrdude_trinket.conf -p attiny85 -c usbtiny -U flash:w:../../bazel-bin/devices/delay_switch/delay_switch.hex
