
# Suppress warnings for external code
if (EXISTS "${CMAKE_SOURCE_DIR}/external/atari800_pokey")
    file(GLOB_RECURSE ATARI800_SOURCES
            "${CMAKE_SOURCE_DIR}/external/atari800_pokey/*.c"
            "${CMAKE_SOURCE_DIR}/external/atari800_pokey/*.h"
    )
    set_source_files_properties(${ATARI800_SOURCES} PROPERTIES COMPILE_FLAGS "-w")
endif ()

set(POKEY_SRC
        external/atari800_pokey/mzpokeysnd.c
        external/atari800_pokey/mzpokeysnd_ext.c
        external/atari800_pokey/pokey.c
        external/atari800_pokey/pokeysnd.c
        external/atari800_pokey/remez.c
)
