#
# dependencies.cmake
#

# silence warnings about CPM
cmake_policy(PUSH)
if(POLICY CMP0097)
  cmake_policy(SET CMP0097 NEW)
endif()


# setup CPM
include(FetchContent)
FetchContent_Declare(
        CPM
        GIT_REPOSITORY https://github.com/cpm-cmake/CPM.cmake
        GIT_TAG v0.42.0 
)
FetchContent_MakeAvailable(CPM)

# doctest
CPMAddPackage(
        NAME doctest
        GITHUB_REPOSITORY doctest/doctest
        VERSION 2.4.12
        OPTIONS "DOCTEST_WITH_MAIN OFF"
)

# fmtlib
CPMAddPackage("gh:fmtlib/fmt#11.2.0")

# tcb-span
set(TCB_SPAN_ENABLE_TESTS OFF CACHE BOOL "" FORCE)
CPMAddPackage(
        NAME tcb-span
        GITHUB_REPOSITORY tcbrindle/span
        GIT_TAG master
        EXCLUDE_FROM_ALL TRUE
)
set(TCB_SPAN_INCLUDE_DIR "${tcb-span_SOURCE_DIR}/include")

# setup SDL if building for host platform
if (NOT LOKEY_TARGET_PICO)
    # SDL2
    find_package(SDL2 REQUIRED)
endif ()

cmake_policy(POP)
