cmake_minimum_required(VERSION 3.25)

# --- PLATFORM-SPECIFIC SETUP ---
if (LOKEY_TARGET_PICO)
    set(PICO_SDK_PATH "${CMAKE_SOURCE_DIR}/pico-sdk" CACHE PATH "Path to the Raspberry Pi Pico SDK")
    set(PICO_EXTRAS_PATH "${CMAKE_SOURCE_DIR}/pico-extras" CACHE PATH "Path to the pico-extras library")
    set(PICO_EXTRAS_ENABLED_PICO_AUDIO 1)
    include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

    project(liblokey C CXX ASM)
    pico_sdk_init()
else ()
    project(liblokey C CXX ASM)
endif ()

# --- COMMON SETUP ---
# This code runs for both Pico and host builds.
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/dependencies.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/source.cmake)

if (LOKEY_TARGET_PICO)
    message(STATUS "Building for Raspberry Pi Pico")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/target_pico.cmake)
else ()
    message(STATUS "Building for host target")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/target_host.cmake)
endif ()