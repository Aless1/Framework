set (INTERFACE
    ${PROJECT_SOURCE_DIR}/module/interface/ITest.h
    ${PROJECT_SOURCE_DIR}/module/interface/IEvent.h
)

set (TEST
    ${PROJECT_SOURCE_DIR}/module/test/Test.h
    ${PROJECT_SOURCE_DIR}/module/test/Test.cc
    ${PROJECT_SOURCE_DIR}/module/test/Main.cc
)

set (EVENT
    ${PROJECT_SOURCE_DIR}/module/event/Event.h
    ${PROJECT_SOURCE_DIR}/module/event/Event.cc
    ${PROJECT_SOURCE_DIR}/module/event/Main.cc
)

INCLUDE_DIRECTORIES(
     "${PROJECT_SOURCE_DIR}/module/interface"
)

add_library(Test
    ${INTERFACE}
    ${TEST}
)

add_library(Event
    ${INTERFACE}
    ${EVENT}
)
