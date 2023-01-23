# -----------------------------------------------------------------------------
# Find required modules
# -----------------------------------------------------------------------------
find_package(Protobuf REQUIRED)
include(common.cmake)

# Proto file
#get_filename_component(proto "../proto/test.proto" ABSOLUTE)
##get_filename_component(proto_path "${proto}" PATH)
#get_filename_component(proto_path "../proto/test.proto" DIRECTORY)

get_filename_component(proto "../proto/test.proto" ABSOLUTE)
get_filename_component(proto_path "${proto}" PATH)

# Generated sources
#set(proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/proto.pb.cc")
#set(proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/proto.pb.h")
#set(grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/proto.grpc.pb.cc")
#set(grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/proto.grpc.pb.h")

set(proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/test.pb.cc")
set(proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/test.pb.h")
set(grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/test.grpc.pb.cc")
set(grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/test.grpc.pb.h")

#set(_PROTOBUF_PROTOC /usr/bin/protoc)
message (blaproto ${_PROTOBUF_PROTOC})
#magic build :)
add_custom_command(
      OUTPUT "${proto_srcs}" "${proto_hdrs}" "${grpc_srcs}" "${grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
#      COMMAND protoc
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${proto}"
      DEPENDS "${proto}"
)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")
add_library(
    grpc_proto
    ${grpc_srcs}
    ${grpc_hdrs}
    ${proto_srcs}
    ${proto_hdrs}
)
target_link_libraries(
    grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
)
