cmake_minimum_required(VERSION 2.8)
project (Framework)
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

SET(CMAKE_CXX_FLAGS "-g -std=c++11")

set (INTERFACE
    ${PROJECT_SOURCE_DIR}/interface/ICM.h
    ${PROJECT_SOURCE_DIR}/interface/ICore.h
    ${PROJECT_SOURCE_DIR}/interface/INet.h
)

set (PUBLIC
    ${PROJECT_SOURCE_DIR}/public/CirBuffer.h
    ${PROJECT_SOURCE_DIR}/public/TPool.h
    ${PROJECT_SOURCE_DIR}/public/Daily.h
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
    ${PROJECT_SOURCE_DIR}/network/kqueue/Associat.h
)


INCLUDE_DIRECTORIES(
    "${PROJECT_SOURCE_DIR}/public"
    "${PROJECT_SOURCE_DIR}/interface")

SOURCE_GROUP(interface FILES ${INTERFACE})
SOURCE_GROUP(public FILES ${PUBLIC})
SOURCE_GROUP(core FILES ${CORE})
SOURCE_GROUP(net FILES ${NET})

add_executable(Framework 
    ${INTERFACE}
    ${PUBLIC}
    ${NET}
    ${CORE}
)
