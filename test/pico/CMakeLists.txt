# CMakeLists.txt
# Pico tests

set(SHARED_TEST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/test/shared)

# test_audio_gpio_pico
add_executable(test_audio_gpio_pico
        ${CMAKE_CURRENT_SOURCE_DIR}/test_audio_gpio_pico.cpp
)
target_link_libraries(test_audio_gpio_pico PRIVATE
        pico_stdlib
)
pico_enable_stdio_usb(test_audio_gpio_pico 1)
pico_enable_stdio_uart(test_audio_gpio_pico 0)
pico_add_extra_outputs(test_audio_gpio_pico)

# test_audio_pio_pico
add_executable(test_audio_pio_pico
        ${CMAKE_CURRENT_SOURCE_DIR}/test_audio_pio_pico.cpp
        ${CMAKE_SOURCE_DIR}/src/audio_pwm.pio
)
pico_generate_pio_header(
        test_audio_pio_pico
        ${CMAKE_SOURCE_DIR}/src/audio_pwm.pio
)
pico_enable_stdio_usb(test_audio_pio_pico 1)
pico_enable_stdio_uart(test_audio_pio_pico 0)
pico_add_extra_outputs(test_audio_pio_pico)

target_link_libraries(test_audio_pio_pico PRIVATE
        pico_stdlib
        hardware_pio
)

# test_gpio_audio_sink_pico
add_executable(test_gpio_audio_sink_pico
        ${CMAKE_CURRENT_SOURCE_DIR}/test_gpio_audio_sink_pico.cpp
        ${CMAKE_SOURCE_DIR}/test/shared/test_audio_sink.cpp
)
target_include_directories(test_gpio_audio_sink_pico PRIVATE ${SHARED_TEST_INCLUDE_DIR})
target_link_libraries(test_gpio_audio_sink_pico PRIVATE liblokey)
pico_enable_stdio_usb(test_gpio_audio_sink_pico 1)
pico_enable_stdio_uart(test_gpio_audio_sink_pico 0)
pico_add_extra_outputs(test_gpio_audio_sink_pico)

# test_pwm_audio_sink_pico
add_executable(test_pwm_audio_sink_pico
        ${CMAKE_CURRENT_SOURCE_DIR}/test_pwm_audio_sink_pico.cpp
        ${CMAKE_SOURCE_DIR}/test/shared/test_audio_sink.cpp
)
target_include_directories(test_pwm_audio_sink_pico PRIVATE ${SHARED_TEST_INCLUDE_DIR})
target_link_libraries(test_pwm_audio_sink_pico PRIVATE liblokey)
pico_enable_stdio_usb(test_pwm_audio_sink_pico 1)
pico_enable_stdio_uart(test_pwm_audio_sink_pico 0)
pico_add_extra_outputs(test_pwm_audio_sink_pico)

# test_audio_sink_a800_pico
add_executable(test_audio_sink_a800_pico
        ${CMAKE_CURRENT_SOURCE_DIR}/test_audio_sink_a800_pico.cpp
        ${CMAKE_SOURCE_DIR}/test/shared/test_audio_sink_a800.cpp
)
target_include_directories(test_audio_sink_a800_pico PRIVATE ${SHARED_TEST_INCLUDE_DIR})
target_link_libraries(test_audio_sink_a800_pico PRIVATE liblokey)
pico_enable_stdio_usb(test_audio_sink_a800_pico 1)
pico_enable_stdio_uart(test_audio_sink_a800_pico 0)
pico_add_extra_outputs(test_audio_sink_a800_pico)
