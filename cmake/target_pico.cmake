#
# target_pico.cmake
#

# setup PICO SDK
set(PICO_BOARD pico)
if (NOT DEFINED PICO_SDK_PATH)
    set(PICO_SDK_PATH "${CMAKE_SOURCE_DIR}/pico-sdk")
endif ()
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)
pico_sdk_init()

set(LOKEY_SRC
        src/lokey.cpp
        src/pico_audio_sink.cpp
        src/atari800_pokey.cpp
)

add_library(liblokey STATIC ${LOKEY_SRC} ${POKEY_SRC})
target_include_directories(liblokey PUBLIC
        include
        src
        external/atari800_pokey/stubs
        external
        ${TCB_SPAN_INCLUDE_DIR}
)
target_link_libraries(liblokey PUBLIC pico_stdlib fmt::fmt)

# hello test to ensure SDK is setup to ensure we can build and flash to pico
add_executable(pico_hello
        test/pico/hello.cpp
)
target_link_libraries(pico_hello
        pico_stdlib
)
pico_enable_stdio_usb(pico_hello 1)
pico_enable_stdio_uart(pico_hello 0)
pico_add_extra_outputs(pico_hello)

# basic output observed with cat /dev/ttyACM0
add_custom_target(flash
        COMMAND ${CMAKE_COMMAND} -E echo "Flashing with picotool..."
        COMMAND picotool load -f $<TARGET_FILE:pico_hello>
        DEPENDS pico_hello
)

