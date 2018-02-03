cmake_minimum_required(VERSION 2.8)
project (tcore)
# set_property(GLOBAL PROPERTY USE_FOLDERS On)
#version
set (FRAMEWORK_VERSION_MAJOR 1)
set (FRAMEWORK_VERSION_MINOR 0)

IF (WIN32)
    MESSAGE(STATUS "Now is windows")
ELSEIF (APPLE)
    MESSAGE(STATUS "Now is Apple system")
ELSEIF (UNIX)
    MESSAGE(STATUS "Now is UNIX")
ENDIF()

set (EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/apple/")
set (LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/apple/")
set (BUILD_SHARED_LIBS On)

SET(CMAKE_CXX_FLAGS "-g -std=c++11 -lcurl")

set (INTERFACE
    ${PROJECT_SOURCE_DIR}/interface/ICM.h
    ${PROJECT_SOURCE_DIR}/interface/ICore.h
    ${PROJECT_SOURCE_DIR}/interface/INet.h
    ${PROJECT_SOURCE_DIR}/interface/IModule.h
    ${PROJECT_SOURCE_DIR}/interface/ILogic.h
    ${PROJECT_SOURCE_DIR}/interface/ITcpHeader.h
    ${PROJECT_SOURCE_DIR}/interface/ILogger.h
    ${PROJECT_SOURCE_DIR}/interface/IHttp.h
    ${PROJECT_SOURCE_DIR}/interface/IHttpHeader.h
)

set (PUBLIC
    ${PROJECT_SOURCE_DIR}/public/CirBuffer.h
    ${PROJECT_SOURCE_DIR}/public/TPool.h
    ${PROJECT_SOURCE_DIR}/public/Daily.h
    ${PROJECT_SOURCE_DIR}/public/Thread.h
    ${PROJECT_SOURCE_DIR}/public/Thread.cc
    ${PROJECT_SOURCE_DIR}/public/TQueue.h
)

set (CORE
    ${PROJECT_SOURCE_DIR}/core/Main.cc
    ${PROJECT_SOURCE_DIR}/core/Core.h
    ${PROJECT_SOURCE_DIR}/core/Core.cc
)

set (NET
    ${PROJECT_SOURCE_DIR}/network/kqueue/Header.h
    ${PROJECT_SOURCE_DIR}/network/kqueue/Net.h
    ${PROJECT_SOURCE_DIR}/network/kqueue/Net.cc
    ${PROJECT_SOURCE_DIR}/network/kqueue/Accept.h
    ${PROJECT_SOURCE_DIR}/network/kqueue/Accept.cc
    ${PROJECT_SOURCE_DIR}/network/kqueue/Pipe.h
    ${PROJECT_SOURCE_DIR}/network/kqueue/Pipe.cc
)

set (LOGIC
    ${PROJECT_SOURCE_DIR}/logic//Logic.h
    ${PROJECT_SOURCE_DIR}/logic//Logic.cc
)

set (LOGGER
    ${PROJECT_SOURCE_DIR}/logger/Logger.h
    ${PROJECT_SOURCE_DIR}/logger/Logger.cc
    ${PROJECT_SOURCE_DIR}/logger/LogFile.h
    ${PROJECT_SOURCE_DIR}/logger/LogFile.cc
)

set (HTTP
    ${PROJECT_SOURCE_DIR}/http//Http.h
    ${PROJECT_SOURCE_DIR}/http//Http.cc
    ${PROJECT_SOURCE_DIR}/http//HttpRequest.h
    ${PROJECT_SOURCE_DIR}/http//HttpRequest.cc
)

INCLUDE_DIRECTORIES(
    "${PROJECT_SOURCE_DIR}/public"
    "${PROJECT_SOURCE_DIR}/interface"
    "${PROJECT_SOURCE_DIR}/third_party/include"
)

set (THIRD_PARTY_INCLUDE
    "${PROJECT_SOURCE_DIR}/third_party/include"
)

set (THIRD_PARTY_LIB
    "${PROJECT_SOURCE_DIR}/third_party/yaml-cpp/libyaml-cpp.0.6.dylib"
)


SOURCE_GROUP(interface FILES ${INTERFACE})
SOURCE_GROUP(public FILES ${PUBLIC})
SOURCE_GROUP(core FILES ${CORE})
SOURCE_GROUP(net FILES ${NET})
SOURCE_GROUP(logic FILES ${LOGIC})
SOURCE_GROUP(logger FILES ${LOGGER})
SOURCE_GROUP(http FILES ${HTTP})

add_executable(tcore
    ${INTERFACE}
    ${PUBLIC}
    ${NET}
    ${CORE}
    ${LOGIC}
    ${LOGGER}
    ${HTTP}
)

target_link_libraries(tcore ${THIRD_PARTY_LIB})

add_subdirectory(module)
