package(default_visibility = ["//visibility:public"])


cc_binary(
    name = "client",
    srcs = ["client_main.cc"],
    deps = [":clientlib"],
)

cc_binary(
    name = "server",
    srcs = ["server.cc"],
    deps = ["//src/proto:cpp"],
)

cc_library(
    name = "clientlib",
    srcs = ["client.cc"],
    hdrs = ["client.h"],
    deps = ["//src/proto:cpp"],
)

