# CMakeLists.txt
# host tests

set(SHARED_TEST_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../shared)

# test_pokey_direct_sdl
add_executable(test_pokey_direct_sdl
        ${CMAKE_CURRENT_SOURCE_DIR}/test_pokey_direct_sdl.cpp
)
target_include_directories(test_pokey_direct_sdl PRIVATE ${SHARED_TEST_INCLUDE_DIR})
target_link_libraries(test_pokey_direct_sdl PRIVATE liblokey SDL2::SDL2)

# test_audio_sink_sdl
add_executable(test_audio_sink_sdl
        ${CMAKE_CURRENT_SOURCE_DIR}/test_audio_sink_sdl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../shared/test_audio_sink.cpp
)
target_include_directories(test_audio_sink_sdl PRIVATE ${SHARED_TEST_INCLUDE_DIR})
target_link_libraries(test_audio_sink_sdl PRIVATE liblokey SDL2::SDL2)

# test_audio_sink_a800_sdl
add_executable(test_audio_sink_a800_sdl
        ${CMAKE_CURRENT_SOURCE_DIR}/test_audio_sink_a800_sdl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../shared/test_audio_sink_a800.cpp
)
target_include_directories(test_audio_sink_a800_sdl PRIVATE ${SHARED_TEST_INCLUDE_DIR})
target_link_libraries(test_audio_sink_a800_sdl PRIVATE liblokey SDL2::SDL2)

# test_lokey
add_executable(test_lokey
        ${CMAKE_CURRENT_SOURCE_DIR}/test_lokey.cpp
)
target_include_directories(test_lokey PRIVATE ${SHARED_TEST_INCLUDE_DIR})
target_link_libraries(test_lokey PRIVATE liblokey SDL2::SDL2)

# test_registers
add_executable(test_registers
        ${CMAKE_CURRENT_SOURCE_DIR}/../shared/test_registers.cpp
)
target_include_directories(test_registers PRIVATE ${SHARED_TEST_INCLUDE_DIR} ${doctest_SOURCE_DIR}/doctest)
target_link_libraries(test_registers PRIVATE liblokey doctest)
