project(smartspeec-demo-plugins C)

# recognition plugin
add_library(
        smartspeech-recognition-demo
        SHARED
        smartspeech-recognition-demo.c
)

target_include_directories(
        smartspeech-recognition-demo
        PUBLIC
        ${CMAKE_SOURCE_DIR}
)
target_link_libraries(
        smartspeech-recognition-demo
        PRIVATE
        recognition
        smartspeech-grpc-client
)
set_target_properties(
        smartspeech-recognition-demo
        PROPERTIES
        PREFIX ""
)

# synthesis plugin
add_library(
        smartspeech-synthesis-demo
        SHARED
        smartspeech-synthesis-demo.c
)

target_include_directories(
        smartspeech-synthesis-demo
        PUBLIC
        ${CMAKE_SOURCE_DIR}
)
target_link_libraries(
        smartspeech-synthesis-demo
        PRIVATE
        synthesis
        smartspeech-grpc-client
)
set_target_properties(
        smartspeech-synthesis-demo
        PROPERTIES
        PREFIX ""
)
