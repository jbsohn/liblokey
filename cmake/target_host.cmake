#
# target_host.cmake
#

set(LOKEY_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/audio/sdl_audio_sink.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/pokey/atari800_pokey.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/pokey/prosystem_pokey.cpp
)

add_library(liblokey STATIC ${LOKEY_SRC} ${POKEY_SRC})
target_include_directories(liblokey PUBLIC
        include
        src
        external/atari800_pokey/stubs
        external
)
target_link_libraries(liblokey PUBLIC SDL2::SDL2)
