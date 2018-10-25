#
# Debugging Library
#
# Copyright (C) 2020, Hensoldt Cyber GmbH
#

cmake_minimum_required(VERSION 3.17)

#-------------------------------------------------------------------------------
project(lib_debug C)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        "src"
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
        lib_compiler
)

if (DEBUG_CONFIG_H_FILE)

    target_compile_definitions(${PROJECT_NAME}
        INTERFACE
            "DEBUG_CONFIG_H_FILE=${DEBUG_CONFIG_H_FILE}"
    )

endif()
