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
# Pico SDK Setup
#
set(PICO_BOARD pico_w)
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# 
# Generic Setup
#
set(FAMILY rp2040)
set(PROJECT RFW)

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

set(MAIN_EXECUTABLE_NAME RFW-main)
set(TEST_EXECUTABLE_NAME RFW-test)
set(CALIBRATOR_EXECUTABLE_NAME RFW-calibrator)
set(LIB_NAME RFW-lib)

#
# Set Language Standards
#
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()


add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-unknown-pragmas
        )


if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()

# enable optimizations for C++ files
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
# enable optimizations for C files
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

# add main.cpp
add_executable(${MAIN_EXECUTABLE_NAME} main.cpp)

# add test.cpp
add_executable(${TEST_EXECUTABLE_NAME} test.cpp)

# add calibrator.cpp
add_executable(${CALIBRATOR_EXECUTABLE_NAME} calibrator.cpp)

# add all .cpp files recursively in src
add_library(${LIB_NAME} STATIC ${SRC_FILES})

# pull in includes for main
target_include_directories(${MAIN_EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${MAIN_EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# pull in includes for test
target_include_directories(${TEST_EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${TEST_EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# pull in includes for calibrator
target_include_directories(${CALIBRATOR_EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${CALIBRATOR_EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# pull in includes for lib
target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# link libs for main
target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE 
    ${LIB_NAME}   
    pico_stdlib
    pico_cyw43_arch_none
    pico_bootrom
    pico_malloc
    pico_runtime
    pico_multicore
    pico_sync
    pico_rand
    hardware_pwm
    hardware_i2c
    hardware_spi
    hardware_watchdog
    hardware_pio
    hardware_dma
    hardware_uart
    hardware_flash
    tinyusb_device
    tinyusb_host
    tinyusb_board
    tinyusb_pico_pio_usb
)

# link libs for test
target_link_libraries(${TEST_EXECUTABLE_NAME} PRIVATE 
    ${LIB_NAME}   
    pico_stdlib
    pico_cyw43_arch_none
    pico_bootrom
    pico_malloc
    pico_runtime
    pico_multicore
    pico_sync
    pico_rand
    hardware_pwm
    hardware_i2c
    hardware_spi
    hardware_watchdog
    hardware_pio
    hardware_dma
    hardware_uart
    hardware_flash
    tinyusb_device
    tinyusb_host
    tinyusb_board
    tinyusb_pico_pio_usb
)

# link libs for test
target_link_libraries(${CALIBRATOR_EXECUTABLE_NAME} PRIVATE 
    ${LIB_NAME}   
    pico_stdlib
    pico_cyw43_arch_none
    pico_bootrom
    pico_malloc
    pico_runtime
    pico_multicore
    pico_sync
    pico_rand
    hardware_pwm
    hardware_i2c
    hardware_spi
    hardware_watchdog
    hardware_pio
    hardware_dma
    hardware_uart
    hardware_flash
    tinyusb_device
    tinyusb_host
    tinyusb_board
    tinyusb_pico_pio_usb
)

# link libs for lib
target_link_libraries(${LIB_NAME} PRIVATE 
    pico_stdlib
    pico_cyw43_arch_none
    pico_bootrom
    pico_malloc
    pico_runtime
    pico_multicore
    pico_sync
    pico_rand
    hardware_pwm
    hardware_i2c
    hardware_spi
    hardware_watchdog
    hardware_pio
    hardware_dma
    hardware_uart
    hardware_flash
    tinyusb_device
    tinyusb_host
    tinyusb_board
    tinyusb_pico_pio_usb
)

target_link_options(${MAIN_EXECUTABLE_NAME} PRIVATE -Xlinker --print-memory-usage)

target_compile_definitions(${MAIN_EXECUTABLE_NAME} PRIVATE
    PICO_PANIC_FUNCTION=tusb_panic
)

set(CMAKE_ROOT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(util)

# Setup stdio interface
pico_enable_stdio_usb(${MAIN_EXECUTABLE_NAME} 0)
pico_enable_stdio_uart(${MAIN_EXECUTABLE_NAME} 0)
pico_enable_stdio_usb(${TEST_EXECUTABLE_NAME} 0)
pico_enable_stdio_uart(${TEST_EXECUTABLE_NAME} 0)
pico_enable_stdio_usb(${CALIBRATOR_EXECUTABLE_NAME} 0)
pico_enable_stdio_uart(${CALIBRATOR_EXECUTABLE_NAME} 0)

# Generate uf2 files
pico_add_extra_outputs(${MAIN_EXECUTABLE_NAME})
pico_add_extra_outputs(${TEST_EXECUTABLE_NAME})
pico_add_extra_outputs(${CALIBRATOR_EXECUTABLE_NAME})

# Copy uf2 files to dist
add_custom_command(TARGET ${MAIN_EXECUTABLE_NAME} POST_BUILD COMMAND 
    ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_LIST_DIR}/build
)
add_custom_command(TARGET ${MAIN_EXECUTABLE_NAME} POST_BUILD COMMAND 
    ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/build/${MAIN_EXECUTABLE_NAME}.uf2 ${CMAKE_CURRENT_LIST_DIR}/dist/${MAIN_EXECUTABLE_NAME}.uf2
)
add_custom_command(TARGET ${TEST_EXECUTABLE_NAME} POST_BUILD COMMAND 
    ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/build/${TEST_EXECUTABLE_NAME}.uf2 ${CMAKE_CURRENT_LIST_DIR}/dist/${TEST_EXECUTABLE_NAME}.uf2
)
add_custom_command(TARGET ${CALIBRATOR_EXECUTABLE_NAME} POST_BUILD COMMAND 
    ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/build/${CALIBRATOR_EXECUTABLE_NAME}.uf2 ${CMAKE_CURRENT_LIST_DIR}/dist/${CALIBRATOR_EXECUTABLE_NAME}.uf2
)
