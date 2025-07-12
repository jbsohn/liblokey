cmake_minimum_required(VERSION 3.25)
project(liblokey C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_SDK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/pico-sdk")
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)
pico_sdk_init()

# Global warnings for your own code
if (MSVC)
    add_compile_options(/W4)
else ()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/dependencies.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/target_host.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/target_pico.cmake)