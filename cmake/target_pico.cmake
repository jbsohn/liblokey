#
# target_pico.cmake
#

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
        pico_audio
        pico_audio_pwm
        pico_util_buffer
)

# --- Test Executables ---
add_executable(pico_hello
        test/pico/hello.cpp
)
target_link_libraries(pico_hello PRIVATE pico_stdlib)
pico_enable_stdio_usb(pico_hello 1)
pico_enable_stdio_uart(pico_hello 0)
pico_add_extra_outputs(pico_hello)

add_custom_target(flash
        COMMAND ${CMAKE_COMMAND} -E echo "Flashing with picotool..."
        COMMAND picotool load -f $<TARGET_FILE:pico_hello>
        DEPENDS pico_hello
)

# test_audio_pico
add_executable(test_audio_pico test/pico/test_audio_pico.cpp)
target_link_libraries(test_audio_pico PRIVATE liblokey)
pico_enable_stdio_usb(test_audio_pico 1)
pico_enable_stdio_uart(test_audio_pico 0)
pico_add_extra_outputs(test_audio_pico)

# test_audio_pwm_pico
add_executable(test_audio_pwm_pico test/pico/test_audio_pwm_pico.cpp)
target_link_libraries(test_audio_pwm_pico PRIVATE
        pico_stdlib
        pico_audio_pwm
)
target_compile_definitions(test_audio_pwm_pico PRIVATE USE_AUDIO_PWM=1)
pico_enable_stdio_usb(test_audio_pwm_pico 1)
pico_enable_stdio_uart(test_audio_pwm_pico 0)
pico_add_extra_outputs(test_audio_pwm_pico)

# test_audio_sink_pico
add_executable(test_audio_sink_pico test/pico/test_audio_sink_pico.cpp)
target_link_libraries(test_audio_sink_pico PRIVATE liblokey)
pico_enable_stdio_usb(test_audio_sink_pico 1)
pico_enable_stdio_uart(test_audio_sink_pico 0)
pico_add_extra_outputs(test_audio_sink_pico)

# test_audio_sink_a800_pico
add_executable(test_audio_sink_a800_pico test/pico/test_audio_sink_a800_pico.cpp)
target_link_libraries(test_audio_sink_a800_pico PRIVATE liblokey)
pico_enable_stdio_usb(test_audio_sink_a800_pico 1)
pico_enable_stdio_uart(test_audio_sink_a800_pico 0)
pico_add_extra_outputs(test_audio_sink_a800_pico)