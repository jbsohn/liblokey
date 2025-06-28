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

# Add Doctest via CPM
CPMAddPackage("gh:doctest/doctest@2.4.11")

# SDL2 support
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# PoKEY stub headers
include_directories(src/pokey/stubs)

# === LIBLOKEY SETUP ===

# Separate source files
set(LOKEY_SRC
        src/lokey.cpp
        src/pokey_adapter.cpp
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
target_compile_definitions(liblokey PRIVATE SOUND_CALLBACK)
# we may want this defined:
#target_compile_definitions(liblokey PRIVATE POKEY_UPDATE)

# Suppress warnings for pokey.c only
if (MSVC)
    set_source_files_properties(${POKEY_SRC} PROPERTIES COMPILE_FLAGS "/w")
else()
    set_source_files_properties(${POKEY_SRC} PROPERTIES COMPILE_FLAGS "-w")
endif()

target_include_directories(liblokey PUBLIC
        include
        src
        src/pokey/stubs
)

# === SDL Audio Test ===

add_executable(test_sdl test/test_pokey_direct_sdl.cpp)
target_link_libraries(test_sdl PRIVATE liblokey ${SDL2_LIBRARIES})

# === Doctest Unit Test ===

add_executable(test_registers test/test_registers.cpp)
target_link_libraries(test_registers PRIVATE liblokey doctest)
target_include_directories(test_registers PRIVATE ${doctest_SOURCE_DIR}/doctest)