#
# target_pico.cmake
#

set(LOKEY_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/audio/pico_gpio_audio_sink.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/audio/pico_pwm_audio_sink.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/pokey/atari800_pokey.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/pokey/prosystem_pokey.cpp
)

add_library(liblokey STATIC ${LOKEY_SRC} ${POKEY_SRC})
target_compile_definitions(liblokey PRIVATE USE_AUDIO_PWM=1)
target_include_directories(liblokey PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/external
        ${CMAKE_CURRENT_SOURCE_DIR}/external/atari800_pokey
        ${CMAKE_CURRENT_SOURCE_DIR}/external/atari800_pokey/stubs
)

target_link_libraries(liblokey PUBLIC
        pico_stdlib
        pico_multicore
        hardware_pwm
)
