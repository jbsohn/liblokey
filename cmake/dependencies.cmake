#
# dependencies.cmake
#

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

# tcb-span
set(TCB_SPAN_ENABLE_TESTS OFF CACHE BOOL "" FORCE)
CPMAddPackage(
        NAME tcb-span
        GITHUB_REPOSITORY tcbrindle/span
        GIT_TAG master
        EXCLUDE_FROM_ALL TRUE
)
set(TCB_SPAN_INCLUDE_DIR "${tcb-span_SOURCE_DIR}/include")

if (NOT LOKEY_TARGET_PICO)
    # SDL2
    find_package(SDL2 REQUIRED)
endif ()
