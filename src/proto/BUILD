package(default_visibility = ["//visibility:public"])

load("//third_party/rules_protobuf/cpp:rules.bzl", "cc_proto_library")


filegroup(
    name = "protos",
    srcs = ["snowflake.proto"],
)

cc_proto_library(
    name = "cpp",
    protos = [":protos"],
)

