# === LIBLOKEY SETUP ===

set(LOKEY_SRC
    src/lokey.cpp
    src/sdl_audio_sink.cpp
    src/atari800_pokey.cpp
)

set(POKEY_SRC
    external/atari800_pokey/mzpokeysnd.c
    external/atari800_pokey/mzpokeysnd_ext.c
    external/atari800_pokey/pokey.c
    external/atari800_pokey/pokeysnd.c
    external/atari800_pokey/remez.c
)

add_library(liblokey STATIC ${LOKEY_SRC} ${POKEY_SRC})
target_include_directories(liblokey PUBLIC
    include
    src
    external/atari800_pokey/stubs
    external
    ${tcb-span_SOURCE_DIR}/include
)
target_link_libraries(liblokey PUBLIC SDL2::SDL2 fmt::fmt)

# Suppress warnings for POKEY_SRC
if (MSVC)
    set_source_files_properties(${POKEY_SRC} PROPERTIES COMPILE_FLAGS "/w")
else ()
    set_source_files_properties(${POKEY_SRC} PROPERTIES COMPILE_FLAGS "-w")
endif ()

# === host Tests ===
add_executable(test_pokey_direct_sdl test/host/test_pokey_direct_sdl.cpp)
target_link_libraries(test_pokey_direct_sdl PRIVATE liblokey SDL2::SDL2 fmt::fmt)

add_executable(test_audio_sink_a800_sdl test/host/test_audio_sink_a800_sdl.cpp)
target_link_libraries(test_audio_sink_a800_sdl PRIVATE liblokey SDL2::SDL2 fmt::fmt)

add_executable(test_audio_sink_sdl test/host/test_audio_sink_sdl.cpp)
target_link_libraries(test_audio_sink_sdl PRIVATE liblokey SDL2::SDL2 fmt::fmt)

add_executable(test_lokey test/host/test_lokey.cpp)
target_link_libraries(test_lokey PRIVATE liblokey SDL2::SDL2 fmt::fmt)

add_executable(test_registers test/shared/test_registers.cpp)
target_link_libraries(test_registers PRIVATE liblokey doctest)
target_include_directories(test_registers PRIVATE ${doctest_SOURCE_DIR}/doctest)