
# TODO: this should only be for the Atari800 LoFi project
add_compile_definitions(NO_CONSOL_SOUND)

# Suppress warnings for external code
if (EXISTS "${CMAKE_SOURCE_DIR}/external/atari800_pokey")
    file(GLOB_RECURSE ATARI800_SOURCES
            "${CMAKE_SOURCE_DIR}/external/atari800_pokey/*.c"
            "${CMAKE_SOURCE_DIR}/external/atari800_pokey/*.h"
    )
    set_source_files_properties(${ATARI800_SOURCES} PROPERTIES COMPILE_FLAGS "-w")
endif ()

if (USE_HIFI)
    set(POKEY_SRC
            ${CMAKE_CURRENT_SOURCE_DIR}/external/atari800_pokey/mzpokeysnd.c
            ${CMAKE_CURRENT_SOURCE_DIR}/external/atari800_pokey/mzpokeysnd_ext.c
            ${CMAKE_CURRENT_SOURCE_DIR}/external/atari800_pokey/pokey.c
            ${CMAKE_CURRENT_SOURCE_DIR}/external/atari800_pokey/pokeysnd.c
            ${CMAKE_CURRENT_SOURCE_DIR}/external/atari800_pokey/remez.c
    )
else ()
    message("configuring LOFI build...")
    set(POKEY_SRC
            ${CMAKE_CURRENT_SOURCE_DIR}/external/atari800_pokey_lofi/pokey.c
            ${CMAKE_CURRENT_SOURCE_DIR}/external/atari800_pokey_lofi/pokeysnd.c
            ${CMAKE_CURRENT_SOURCE_DIR}/external/atari800_pokey_lofi/globals.c
            ${CMAKE_CURRENT_SOURCE_DIR}/external/atari800_pokey_lofi/pokeysnd_adapter.c
    )
endif ()