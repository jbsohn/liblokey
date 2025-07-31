#
# target_pico.cmake
#

function(always_build_uf2_for_target target_name)
    add_custom_command(
        OUTPUT ${target_name}.uf2
        COMMAND ${PICO_SDK_PATH}/tools/elf2uf2/elf2uf2 $<TARGET_FILE:${target_name}> ${target_name}.uf2
        # The magic below: depend on the .elf *and* all sources for this target!
        DEPENDS ${target_name} $<TARGET_PROPERTY:${target_name},SOURCES>
        COMMENT "Generating ${target_name}.uf2"
    )
    add_custom_target(${target_name}_uf2 ALL DEPENDS ${target_name}.uf2)
endfunction()

set(LOKEY_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lokey.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/pico_audio_sink.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/atari800_pokey.cpp
)

add_library(liblokey STATIC ${LOKEY_SRC} ${POKEY_SRC})
target_compile_definitions(liblokey PRIVATE USE_AUDIO_PWM=1)
target_include_directories(liblokey PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/external
        ${CMAKE_CURRENT_SOURCE_DIR}/external/atari800_pokey
        ${CMAKE_CURRENT_SOURCE_DIR}/external/atari800_pokey/stubs
        ${TCB_SPAN_INCLUDE_DIR}
)

target_link_libraries(liblokey PUBLIC
        pico_stdlib
        pico_multicore
        hardware_pwm
)

# test_audio_gpio_pico
add_executable(test_audio_gpio_pico
        test/pico/test_audio_gpio_pico.cpp
)
always_build_uf2_for_target(test_audio_gpio_pico)
target_link_libraries(test_audio_gpio_pico PRIVATE
        pico_stdlib
)

# test_audio_pio_pico
add_executable(test_audio_pio_pico
        test/pico/test_audio_pio_pico.cpp
        src/audio_pwm.pio
)
always_build_uf2_for_target(test_audio_pio_pico)
pico_generate_pio_header(
        test_audio_pio_pico
        ${CMAKE_CURRENT_SOURCE_DIR}/src/audio_pwm.pio
)
target_link_libraries(test_audio_pio_pico PRIVATE
        pico_stdlib
        hardware_pio
)

# test_audio_sink_pico
add_executable(test_audio_sink_pico test/pico/test_audio_sink_pico.cpp)
always_build_uf2_for_target(test_audio_sink_pico)
target_link_libraries(test_audio_sink_pico PRIVATE liblokey)

# test_audio_sink_a800_pico
add_executable(test_audio_sink_a800_pico test/pico/test_audio_sink_a800_pico.cpp)
always_build_uf2_for_target(test_audio_sink_a800_pico)
target_link_libraries(test_audio_sink_a800_pico PRIVATE liblokey)

