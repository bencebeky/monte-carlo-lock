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
    srcs = ["combination.cc"],
    hdrs = ["combination.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "related",
    hdrs = ["related.h"],
    visibility = ["//visibility:public"],
    deps = ["view"],
)

cc_binary(
    name = "recursive",
    srcs = ["recursive.cc"],
    deps = [
        "combination",
        "related",
        "view",
    ],
)
