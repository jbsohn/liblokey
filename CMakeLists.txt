cmake_minimum_required(VERSION 3.25)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/source.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/dependencies.cmake)

if (LOKEY_TARGET_PICO)
    message(STATUS "Building for Raspberry Pi Pico")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/target_pico.cmake)
else ()
    message(STATUS "Building for host target")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/target_host.cmake)
endif ()

project(liblokey C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

