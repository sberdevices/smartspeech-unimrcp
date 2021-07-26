set(UNIMRCP_MODULES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/unimrcp/modules)
file(GLOB MRCP_SOFIASIP_SRCS  "${UNIMRCP_MODULES_DIR}/mrcp-sofiasip/src/*.c")
file(GLOB MRCP_UNIRTSP_SRCS "${UNIMRCP_MODULES_DIR}/mrcp-unirtsp/src/*.c")

set(UNIMRCP_LIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/unimrcp/libs")
file(GLOB APR_TOOLKIT_SRCS  "${UNIMRCP_LIBS_DIR}/apr-toolkit/src/*.c")
file(GLOB MPF_CODECS_SRCS "${UNIMRCP_LIBS_DIR}/mpf/codecs/g711/*.c")
file(GLOB MPF_SRCS "${UNIMRCP_LIBS_DIR}/mpf/src/*.c")

file(GLOB MRCP_SRCS "${UNIMRCP_LIBS_DIR}/mrcp/src/*.c")
file(GLOB MRCP_MESSAGE_SRCS "${UNIMRCP_LIBS_DIR}/mrcp/message/src/*.c")
file(GLOB MRCP_CONTROL_SRCS "${UNIMRCP_LIBS_DIR}/mrcp/control/src/*.c")
file(GLOB MRCP_RESOURCES_SRCS "${UNIMRCP_LIBS_DIR}/mrcp/resources/src/*.c")

file(GLOB MRCP_CLIENT_SRCS "${UNIMRCP_LIBS_DIR}/mrcp-client/src/*.c")
file(GLOB MRCP_SERVER_SRCS "${UNIMRCP_LIBS_DIR}/mrcp-server/src/*.c")
file(GLOB MRCP_ENGINE_SRCS "${UNIMRCP_LIBS_DIR}/mrcp-engine/src/*.c")
file(GLOB MRCP_SIG_SRCS  "${UNIMRCP_LIBS_DIR}/mrcp-signaling/src/*.c")
file(GLOB UNI_RTSP_SRCS  "${UNIMRCP_LIBS_DIR}/uni-rtsp/src/*.c")
file(GLOB MRCP_TRANSPORT_SRCS "${UNIMRCP_LIBS_DIR}/mrcpv2-transport/src/*.c")

add_library(uni
        STATIC
        ${MRCP_SOFIASIP_SRCS}
        ${MRCP_UNIRTSP_SRCS}
        ${APR_TOOLKIT_SRCS}
        ${MPF_CODECS_SRCS}
        ${MPF_SRCS}
        ${MRCP_SRCS}
        ${MRCP_MESSAGE_SRCS}
        ${MRCP_CONTROL_SRCS}
        ${MRCP_RESOURCES_SRCS}
        ${MRCP_CLIENT_SRCS}
        ${MRCP_SERVER_SRCS}
        ${MRCP_ENGINE_SRCS}
        ${MRCP_SIG_SRCS}
        ${UNI_RTSP_SRCS}
        ${MRCP_TRANSPORT_SRCS}
        )
target_include_directories(uni
        PUBLIC
        ${APR_INCLUDE_DIRS}
        ${APU_INCLUDE_DIRS}
        ${UNIMRCP_MODULES_DIR}/mrcp-sofiasip/include
        ${UNIMRCP_MODULES_DIR}/mrcp-unirtsp/include
        ${UNIMRCP_LIBS_DIR}/apr-toolkit/include
        ${UNIMRCP_LIBS_DIR}/mpf/include
        ${UNIMRCP_LIBS_DIR}/mpf/codecs
        ${UNIMRCP_LIBS_DIR}/mrcp/include
        ${UNIMRCP_LIBS_DIR}/mrcp/message/include
        ${UNIMRCP_LIBS_DIR}/mrcp/control/include
        ${UNIMRCP_LIBS_DIR}/mrcp/resources/include
        ${UNIMRCP_LIBS_DIR}/mrcp-client/include
        ${UNIMRCP_LIBS_DIR}/mrcp-server/include
        ${UNIMRCP_LIBS_DIR}/mrcp-engine/include
        ${UNIMRCP_LIBS_DIR}/mrcp-signaling/include
        ${UNIMRCP_LIBS_DIR}/uni-rtsp/include
        ${UNIMRCP_LIBS_DIR}/mrcpv2-transport/include
        )

target_link_libraries(uni PUBLIC PkgConfig::SOFIA ${APR_LIBRARIES} ${APU_LIBRARIES})
set_target_properties(uni PROPERTIES POSITION_INDEPENDENT_CODE ON)