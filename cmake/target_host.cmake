#
# target_host.cmake
#

set(LOKEY_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lokey.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sdl_audio_sink.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/atari800_pokey.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/prosystem_pokey.cpp
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
