cmake_minimum_required(VERSION 3.12)
project(BlitzScriptInterpreter)

set(CMAKE_C_STANDARD 11)

set(SOURCES
    main.c
    Miku.rc
)

add_executable(BlitzScriptInterpreter ${SOURCES})

target_link_libraries(BlitzScriptInterpreter ntdll)

if(WIN32)
    set_target_properties(BlitzScriptInterpreter PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
endif()
