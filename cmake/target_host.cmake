#
# target_host.cmake
#

set(LOKEY_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lokey.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sdl_audio_sink.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/atari800_pokey.cpp
)

add_library(liblokey STATIC ${LOKEY_SRC} ${POKEY_SRC})
target_include_directories(liblokey PUBLIC
        include
        src
        external/atari800_pokey/stubs
        external
        ${tcb-span_SOURCE_DIR}/include
)
target_link_libraries(liblokey PUBLIC SDL2::SDL2)

# test_pokey_direct_sdl
add_executable(test_pokey_direct_sdl
        test/host/test_pokey_direct_sdl.cpp
)
target_include_directories(test_pokey_direct_sdl PRIVATE test/shared)
target_link_libraries(test_pokey_direct_sdl PRIVATE liblokey SDL2::SDL2)

# test_audio_sink_sdl
add_executable(test_audio_sink_sdl
        test/host/test_audio_sink_sdl.cpp
        test/shared/test_audio_sink.cpp
)
target_include_directories(test_audio_sink_sdl PRIVATE test/shared)
target_link_libraries(test_audio_sink_sdl PRIVATE liblokey SDL2::SDL2)

# test_audio_sink_a800_sdl
add_executable(test_audio_sink_a800_sdl
        test/host/test_audio_sink_a800_sdl.cpp
        test/shared/test_audio_sink_a800.cpp
)
target_include_directories(test_audio_sink_a800_sdl PRIVATE test/shared)
target_link_libraries(test_audio_sink_a800_sdl PRIVATE liblokey SDL2::SDL2)

# test_lokey
add_executable(test_lokey
        test/host/test_lokey.cpp
)
target_include_directories(test_lokey PRIVATE test/shared)
target_link_libraries(test_lokey PRIVATE liblokey SDL2::SDL2)

# test_registers
add_executable(test_registers
        test/shared/test_registers.cpp
)
target_link_libraries(test_registers PRIVATE liblokey doctest)
target_include_directories(test_registers PRIVATE ${doctest_SOURCE_DIR}/doctest)
