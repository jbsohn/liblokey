cmake_minimum_required(VERSION 3.25)
project(liblokey C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Fetch CPM.cmake from GitHub with a stable version tag
include(FetchContent)
FetchContent_Declare(
        CPM
        GIT_REPOSITORY https://github.com/cpm-cmake/CPM.cmake
        GIT_TAG master
)
FetchContent_MakeAvailable(CPM)

# Add Doctest via CPM
CPMAddPackage("gh:doctest/doctest@2.4.11")

# SDL2 support
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# liblokey static library
add_library(liblokey STATIC
    src/lokey.c
    src/pokey/pokey.c
)

target_include_directories(liblokey PUBLIC include)

# SDL audio test
add_executable(test_sdl test/test_sdl.cpp)
target_link_libraries(test_sdl PRIVATE liblokey ${SDL2_LIBRARIES})

# Doctest unit test
add_executable(test_registers test/test_registers.cpp)
target_link_libraries(test_registers PRIVATE liblokey doctest)
target_compile_definitions(test_registers PRIVATE DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)
