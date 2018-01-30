set (INTERFACE
    ${PROJECT_SOURCE_DIR}/module/interface/ITest.h
)

set (TEST
    ${PROJECT_SOURCE_DIR}/module/test/Test.h
    ${PROJECT_SOURCE_DIR}/module/test/Test.cc
    ${PROJECT_SOURCE_DIR}/module/test/Main.cc
)

INCLUDE_DIRECTORIES(
     "${PROJECT_SOURCE_DIR}/module/interface"
)

add_library(Test
    ${INTERFACE}
    ${TEST}
)
