cmake_minimum_required(VERSION 3.14)
project(smartspeech-unimrcp C CXX)
set(CMAKE_CXX_STANDARD 17)

# Path with FindXXX scripts
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(FindPkgConfig)
pkg_check_modules(SOFIA REQUIRED IMPORTED_TARGET sofia-sip-ua)

set(APR_PKGCONFIG_PATH "/opt/apr/lib/pkgconfig")
set(ENV{PKG_CONFIG_PATH} "${APR_PKGCONFIG_PATH}")

set(APR_SOURCE_DIR "/opt/apr")
set(APU_SOURCE_DIR "/opt/apr")
find_package(APR REQUIRED)
find_package(APRUtil REQUIRED)

pkg_check_modules(CURL REQUIRED IMPORTED_TARGET libcurl)

add_subdirectory(contrib)

find_package(OpenSSL REQUIRED)
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
find_package(nlohmann_json REQUIRED)

add_subdirectory(grpc_client)
add_subdirectory(recognition)
add_subdirectory(synthesis)
add_subdirectory(plugin)