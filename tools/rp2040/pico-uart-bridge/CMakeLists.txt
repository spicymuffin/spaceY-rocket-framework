cmake_minimum_required(VERSION 3.25)

if (NOT PICO_SDK_PATH)
    if(DEFINED ENV{PICO_SDK_PATH})
        set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
        message("Setting PICO_SDK_PATH from environment ('${PICO_SDK_PATH}')")
    else()
        set(PICO_SDK_PATH ${CMAKE_CURRENT_LIST_DIR}/libs/pico-sdk)
        message("Setting PICO_SDK_PATH from git submodule path ('${PICO_SDK_PATH}')")
    endif()
else()
    message("PICO_SDK_PATH already set ('${PICO_SDK_PATH}')")
endif()

set(PICO_BOARD pico_w)

#
# Include pico_sdk_import.cmake from pico-sdk
#
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico-uart-bridge)

pico_sdk_init()

add_executable(uart-bridge uart-bridge.c usb-descriptors.c)

target_include_directories(uart-bridge PUBLIC
	./
	pico-sdk/lib/tinyusb/src)

target_link_libraries(uart-bridge
	hardware_flash
	pico_multicore
	pico_stdlib
	tinyusb_device)

pico_add_extra_outputs(uart-bridge)

if (DEFINED CMAKE_ROOT_LIST_DIR)
    add_custom_command(TARGET uart-bridge POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_ROOT_LIST_DIR}/dist/util
    )
    add_custom_command(TARGET uart-bridge POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_ROOT_LIST_DIR}/build/util/pico-uart-bridge/uart-bridge.uf2
        ${CMAKE_ROOT_LIST_DIR}/dist/util/uart-bridge.uf2
    )
endif()