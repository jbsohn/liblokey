
# Suppress warnings for external code
if (EXISTS "${CMAKE_SOURCE_DIR}/external/atari800_pokey_embed")
    file(GLOB_RECURSE ATARI800_SOURCES
            "${CMAKE_SOURCE_DIR}/external/atari800_pokey_embed/*.c"
            "${CMAKE_SOURCE_DIR}/external/atari800_pokey_embed/*.h"
    )
    set_source_files_properties(${ATARI800_SOURCES} PROPERTIES COMPILE_FLAGS "-w")
endif ()

set(POKEY_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/external/atari800_pokey_embed/mzpokeysnd.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/external/atari800_pokey_embed/pokey.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/external/atari800_pokey_embed/pokeysnd.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/external/atari800_pokey_embed/remez.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/external/atari800_pokey_embed/pokey_utils.cpp
)
