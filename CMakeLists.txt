cmake_minimum_required(VERSION 3.22)

#
# Set PICO_SDK_PATH
#
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

#
# Set PICO_TINYUSB_PATH
#
if (NOT PICO_TINYUSB_PATH)
    if(DEFINED ENV{PICO_TINYUSB_PATH})
        set(PICO_TINYUSB_PATH $ENV{PICO_TINYUSB_PATH})
        message("Setting PICO_TINYUSB_PATH from environment ('${PICO_TINYUSB_PATH}')")
    else()
        set(PICO_TINYUSB_PATH ${CMAKE_CURRENT_LIST_DIR}/lib/tinyusb)
        message("Setting PICO_TINYUSB_PATH from git submodule path ('${PICO_TINYUSB_PATH}')")
    endif()
else()
    message("PICO_TINYUSB_PATH already set ('${PICO_TINYUSB_PATH}')")
endif()

#
# Extract Dependencies for PICO_TINYUSB_PATH
# This enables Pico-PIO-USB
#
find_package(Python3 COMPONENTS Interpreter)
execute_process(COMMAND ${Python3_EXECUTABLE} ${PICO_TINYUSB_PATH}/tools/get_deps.py rp2040)

# 
# Generic Setup
#
set(FAMILY rp2040)
set(PROJECT RFW)
set(PICO_CXX_ENABLE_EXCEPTIONS 1)
set(PICO_CXX_ENABLE_RTTI 1)

#
# Pico SDK Setup
#
set(PICO_BOARD pico_w)
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)


#
# TinyUSB setup
#
include(${PICO_TINYUSB_PATH}/hw/bsp/family_support.cmake)
family_initialize_project(${PROJECT} ${CMAKE_CURRENT_LIST_DIR})
# family_add_pico_pio_usb(${PROJECT})


#
# Configure Project, Executables and Libraries
#
project(${PROJECT} VERSION 1.0 DESCRIPTION "SpaceY Rocket Framework" LANGUAGES C CXX ASM)

#
# Set Language Standards
#
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

add_subdirectory(lib/rfw)
add_subdirectory(lib/ff15)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(${PROJECT}_main ${SOURCES})

set(HARDWARE_LIBRARIES
    fatfs
    pico_stdlib
    pico_malloc
    pico_util
    pico_multicore
    hardware_i2c
    hardware_spi
    tinyusb_device
    tinyusb_host
    tinyusb_board
    tinyusb_pico_pio_usb
)

target_link_libraries(${PROJECT}_main PRIVATE
    rfw
    ${HARDWARE_LIBRARIES}
)
target_link_options(${PROJECT}_main PRIVATE -Xlinker --print-memory-usage)

target_include_directories(${PROJECT}_main PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/firmware
    ${CMAKE_CURRENT_LIST_DIR}/include/tinyusb
    ${CMAKE_CURRENT_LIST_DIR}/lib/rfw/include
    ${CMAKE_CURRENT_LIST_DIR}/lib/ff15
)

pico_add_extra_outputs(${PROJECT}_main)
