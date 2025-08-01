#
# target_pico.cmake
#

set(LOKEY_SRC
        ${CMAKE_SOURCE_DIR}/src/lokey.cpp
        ${CMAKE_SOURCE_DIR}/src/pico_audio_sink.cpp
        ${CMAKE_SOURCE_DIR}/src/atari800_pokey.cpp
)

add_library(liblokey STATIC ${LOKEY_SRC} ${POKEY_SRC})
target_compile_definitions(liblokey PRIVATE USE_AUDIO_PWM=1)
target_include_directories(liblokey PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/external
        ${CMAKE_SOURCE_DIR}/external/atari800_pokey
        ${CMAKE_SOURCE_DIR}/external/atari800_pokey/stubs
)

target_link_libraries(liblokey PUBLIC
        pico_stdlib
        pico_multicore
        hardware_pwm
)
