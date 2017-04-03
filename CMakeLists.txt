cmake_minimum_required(VERSION 3.3)
project(snowflake)

find_package(Protobuf REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

set(PROTO_PATH "${CMAKE_SOURCE_DIR}/src/proto")
set(SNOWFLAKE_PROTO "${PROTO_PATH}/snowflake.proto")
set(GENERATED_PROTOBUF_PATH "${CMAKE_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${GENERATED_PROTOBUF_PATH})

set(SNOWFLAKE_PB_CPP_FILE "${GENERATED_PROTOBUF_PATH}/snowflake.pb.cc")
set(SNOWFLAKE_PB_H_FILE "${GENERATED_PROTOBUF_PATH}/snowflake.pb.h")
set(SNOWFLAKE_GRPC_PB_CPP_FILE "${GENERATED_PROTOBUF_PATH}/snowflake.grpc.pb.cc")
set(SNOWFLAKE_GRPC_PB_H_FILE "${GENERATED_PROTOBUF_PATH}/snowflake.grpc.pb.h")
add_custom_command(
    OUTPUT "${SNOWFLAKE_PB_H_FILE}"
           "${SNOWFLAKE_PB_CPP_FILE}"
           "${SNOWFLAKE_GRPC_PB_H_FILE}"
           "${SNOWFLAKE_GRPC_PB_CPP_FILE}"
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS "--proto_path=${PROTO_PATH}"
         "--cpp_out=${GENERATED_PROTOBUF_PATH}"
         "${SNOWFLAKE_PROTO}"
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS "--proto_path=${PROTO_PATH}"
         "--grpc_out=${GENERATED_PROTOBUF_PATH}"
         "--plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin"
         "${SNOWFLAKE_PROTO}"
    )
set(GENERATED_PROTOBUF_FILES ${SNOWFLAKE_PB_H_FILE} ${SNOWFLAKE_PB_CPP_FILE}
    ${SNOWFLAKE_GRPC_PB_H_FILE} ${SNOWFLAKE_GRPC_PB_CPP_FILE})

include_directories(${GENERATED_PROTOBUF_PATH})
link_libraries(grpc++_unsecure grpc gpr ${PROTOBUF_LIBRARY})

add_executable(server src/core/server.cc ${GENERATED_PROTOBUF_FILES})
add_executable(client src/core/client_main.cc src/core/client.cc ${GENERATED_PROTOBUF_FILES})

