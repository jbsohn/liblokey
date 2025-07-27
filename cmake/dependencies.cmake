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

# setup SDL if building for host platform
if (NOT LOKEY_TARGET_PICO)
    # SDL2
    find_package(SDL2 REQUIRED)
endif ()

cmake_policy(POP)
