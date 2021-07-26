project(recognition CXX C)
set(CMAKE_CXX_STANDARD 17)
set(
        SRCS
        cimpl.cpp
        engine.cpp
        channel.cpp
        event_loop.cpp
)

add_library(recognition OBJECT ${SRCS})
set_target_properties(recognition PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(
        recognition
        PUBLIC
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
        recognition
        PUBLIC
        uni
        smartspeech-grpc-client
)