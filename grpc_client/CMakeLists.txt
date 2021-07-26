project(smartspeech_grpc_client CXX)
set(CMAKE_CXX_STANDARD 17)

set(recognition_proto "${CMAKE_CURRENT_SOURCE_DIR}/recognition.proto")
get_filename_component(recognition_proto "${recognition_proto}" ABSOLUTE)
get_filename_component(recognition_proto_path "${recognition_proto}" PATH)

set(recognition_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/recognition.pb.cc")
set(recognition_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/recognition.pb.h")
set(recognition_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/recognition.grpc.pb.cc")
set(recognition_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/recognition.grpc.pb.h")

get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)

add_custom_command(
        OUTPUT "${recognition_proto_srcs}" "${recognition_proto_hdrs}" "${recognition_grpc_srcs}" "${recognition_grpc_hdrs}"
        COMMAND protobuf::protoc
        ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${recognition_proto_path}"
        --plugin=protoc-gen-grpc="${grpc_cpp_plugin_location}"
        "${recognition_proto}"
        DEPENDS "${recognition_proto}" protobuf::protoc)

set(synthesis_proto "${CMAKE_CURRENT_SOURCE_DIR}/synthesis.proto")
get_filename_component(synthesis_proto "${synthesis_proto}" ABSOLUTE)
get_filename_component(synthesis_proto_path "${synthesis_proto}" PATH)

set(synthesis_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/synthesis.pb.cc")
set(synthesis_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/synthesis.pb.h")
set(synthesis_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/synthesis.grpc.pb.cc")
set(synthesis_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/synthesis.grpc.pb.h")

add_custom_command(
        OUTPUT "${synthesis_proto_srcs}" "${synthesis_proto_hdrs}" "${synthesis_grpc_srcs}" "${synthesis_grpc_hdrs}"
        COMMAND protobuf::protoc
        ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${synthesis_proto_path}"
        --plugin=protoc-gen-grpc="${grpc_cpp_plugin_location}"
        "${synthesis_proto}"
        DEPENDS "${synthesis_proto}" protobuf::protoc)

add_library(smartspeech-grpc-client
        client.cpp
        client.hpp
        token_resolver.cpp
        token_resolver.hpp
        ${recognition_proto_srcs}
        ${recognition_proto_hdrs}
        ${recognition_grpc_srcs}
        ${recognition_grpc_hdrs}
        ${synthesis_proto_srcs}
        ${synthesis_proto_hdrs}
        ${synthesis_grpc_srcs}
        ${synthesis_grpc_hdrs})
set_target_properties(smartspeech-grpc-client PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_link_libraries(smartspeech-grpc-client
        PUBLIC
        PkgConfig::CURL
        nlohmann_json::nlohmann_json
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
        ${APR_LIBRARIES})

target_include_directories(smartspeech-grpc-client PUBLIC ${CMAKE_CURRENT_BINARY_DIR} ${APR_INCLUDE_DIRS})
