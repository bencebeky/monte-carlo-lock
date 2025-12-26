package(default_visibility = ["//visibility:public"])

cc_library(
    name = "view",
    hdrs = ["view.h"],
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
)

cc_library(
    name = "related",
    hdrs = ["related.h"],
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

cc_binary(
    name = "memoize",
    srcs = ["memoize.cc"],
    deps = [
        "combination",
        "related",
        "view",
    ],
)

cc_binary(
    name = "construct",
    srcs = ["construct.cc"],
    deps = [
        "combination",
        "@abseil-cpp//absl/strings",
    ],
)
