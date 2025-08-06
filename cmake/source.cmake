
# Suppress warnings for external code
if (EXISTS "${CMAKE_SOURCE_DIR}/external/atari800_pokey")
    file(GLOB_RECURSE ATARI800_SOURCES
            "${CMAKE_SOURCE_DIR}/external/atari800_pokey/*.c"
            "${CMAKE_SOURCE_DIR}/external/atari800_pokey/*.h"
    )
    set_source_files_properties(${ATARI800_SOURCES} PROPERTIES COMPILE_FLAGS "-w")
endif ()

set(POKEY_SRC
        ${CMAKE_SOURCE_DIR}/external/atari800_pokey/mzpokeysnd.c
        ${CMAKE_SOURCE_DIR}/external/atari800_pokey/mzpokeysnd_ext.c
        ${CMAKE_SOURCE_DIR}/external/atari800_pokey/pokey.c
        ${CMAKE_SOURCE_DIR}/external/atari800_pokey/pokeysnd.c
        ${CMAKE_SOURCE_DIR}/external/atari800_pokey/pokey_resample.c
        ${CMAKE_SOURCE_DIR}/external/atari800_pokey/remez.c
        ${CMAKE_SOURCE_DIR}/external/prosystem_pokey/pokey.c
)
