cc_library(
    name = "view",
    hdrs = ["view.h"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "view_test",
    srcs = ["view_test.cc"],
    deps = [
        "view",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "combination",
    hdrs = ["combination.h"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "recursive",
    srcs = ["recursive.cc"],
    deps = [
        "combination",
        "view",
    ],
)
