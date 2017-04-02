package(default_visibility = ["//visibility:public"])

load("@org_pubref_rules_protobuf//cpp:rules.bzl", "cc_proto_library")

filegroup(
    name = "protos",
    srcs = ["snowflake.proto"],
)

cc_proto_library(
    name = "cpp",
    protos = [":protos"],
)

