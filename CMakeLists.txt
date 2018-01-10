cmake_minimum_required(VERSION 3.10)
project (Framework)

#version
set (FRAMEWORK_VERSION_MAJOR 1)
set (FRAMEWORK_VERSION_MINOR 0)

set (CORE
    core/Main.cc
)

add_executable(Framework ${CORE})
