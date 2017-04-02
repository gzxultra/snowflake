package(default_visibility = ["//visibility:public"])

load("//cpp:rules.bzl", "cc_proto_library")


filegroup(
    name = "protos",
    srcs = ["snowflake.proto"],
)

cc_proto_library(
    name = "cpp",
    proto_deps = [
        "//src/proto:cpp",
    ],
    protos = [":protos"],
    verbose = 0,
    with_grpc = True,
)

