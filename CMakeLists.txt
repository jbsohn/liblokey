cmake_minimum_required(VERSION 3.25)

# Suppress warnings for external code
if (EXISTS "${CMAKE_SOURCE_DIR}/external/atari800_pokey")
    file(GLOB_RECURSE ATARI800_SOURCES
            "${CMAKE_SOURCE_DIR}/external/atari800_pokey/*.c"
            "${CMAKE_SOURCE_DIR}/external/atari800_pokey/*.h"
    )
    set_source_files_properties(${ATARI800_SOURCES} PROPERTIES COMPILE_FLAGS "-w")
endif ()

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

if (MSVC)
    add_compile_options(/W4)
else ()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/dependencies.cmake)


