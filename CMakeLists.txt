cmake_minimum_required(VERSION 3.25)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (LOKEY_TARGET_PICO)
    set(PICO_SDK_PATH "${CMAKE_SOURCE_DIR}/pico-sdk" CACHE PATH "Path to the Raspberry Pi Pico SDK")

    include(${PICO_SDK_PATH}/pico_sdk_init.cmake)
    pico_sdk_init()

    project(liblokey C CXX ASM)
else ()
    project(liblokey C CXX ASM)
endif ()

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/dependencies.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/source.cmake)

if (LOKEY_TARGET_PICO)
    message(STATUS "Building for Raspberry Pi Pico")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/target_pico.cmake)
else ()
    message(STATUS "Building for host target")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/target_host.cmake)
endif ()
