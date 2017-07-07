# Simple Unit Testing for C
# https://github.com/ThrowTheSwitch/Unity/archive/v2.4.1.zip
# LICENSE: MIT

VERSION = "unity_2_4_1"

cc_library(
  name = "unity",
  srcs = [
    VERSION + "/src/unity.c", 
    VERSION + "/src/unity_internals.h",
  ],
  hdrs = [VERSION + "/src/unity.h"],
  visibility = ["//visibility:public"],
)

cc_library(
    name = "unity_framework",
    hdrs = [VERSION + "/extras/fixture/src/unity_fixture.h"],
    srcs = [
      VERSION + "/extras/fixture/src/unity_fixture.c",
      VERSION + "/extras/fixture/src/unity_fixture_internals.h",
      VERSION + "/extras/fixture/src/unity_fixture_malloc_overrides.h",
    ],
    deps = [":unity"],
    visibility = ["//visibility:public"],
)
