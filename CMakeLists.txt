cmake_minimum_required(VERSION 3.25)
project(liblokey C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Global warnings for your own code
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Fetch CPM.cmake from GitHub
include(FetchContent)
FetchContent_Declare(
        CPM
        GIT_REPOSITORY https://github.com/cpm-cmake/CPM.cmake
        GIT_TAG master
)
FetchContent_MakeAvailable(CPM)

# doctest
CPMAddPackage(
        NAME doctest
        GITHUB_REPOSITORY doctest/doctest
        VERSION 2.4.11
        OPTIONS "DOCTEST_WITH_MAIN OFF"
)

# fmtlib
CPMAddPackage("gh:fmtlib/fmt#11.2.0")

set(TCB_SPAN_ENABLE_TESTS OFF CACHE BOOL "" FORCE)
CPMAddPackage(
        NAME tcb-span
        GITHUB_REPOSITORY tcbrindle/span
        GIT_TAG master
        EXCLUDE_FROM_ALL TRUE
)
# SDL2 support
find_package(SDL2 REQUIRED)

# === LIBLOKEY SETUP ===

# Separate source files
set(LOKEY_SRC
        src/lokey.cpp
        src/sdl_audio_sink.cpp
        src/atari800_pokey.cpp
)
set(POKEY_SRC
        src/pokey/mzpokeysnd.c
        src/pokey/mzpokeysnd_ext.c
        src/pokey/pokey.c
        src/pokey/pokeysnd.c
        src/pokey/remez.c
)

# Create the static library from both
add_library(liblokey STATIC ${LOKEY_SRC} ${POKEY_SRC})
target_include_directories(liblokey PUBLIC
        include
        src
        src/pokey/stubs
        ${tcb-span_SOURCE_DIR}/include
)
target_link_libraries(liblokey PUBLIC SDL2::SDL2 fmt::fmt)


# Suppress warnings for POKEY_SRC only
if (MSVC)
    set_source_files_properties(${POKEY_SRC} PROPERTIES COMPILE_FLAGS "/w")
else()
    set_source_files_properties(${POKEY_SRC} PROPERTIES COMPILE_FLAGS "-w")
endif()

target_include_directories(liblokey
        PUBLIC include src
        PRIVATE src/pokey/stubs
)

# === SDL Audio Test ===
add_executable(test_pokey_direct_sdl test/test_pokey_direct_sdl.cpp)
target_link_libraries(test_pokey_direct_sdl PRIVATE liblokey SDL2::SDL2 fmt::fmt)

# === SDL Audio Test ===
add_executable(test_audio_sink_a800_sdl test/test_audio_sink_a800_sdl.cpp)
target_link_libraries(test_audio_sink_a800_sdl PRIVATE liblokey SDL2::SDL2 fmt::fmt)

# === Doctest Unit Test ===
add_executable(test_registers test/test_registers.cpp)
target_link_libraries(test_registers PRIVATE liblokey doctest)
target_include_directories(test_registers PRIVATE ${doctest_SOURCE_DIR}/doctest)
