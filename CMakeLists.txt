cmake_minimum_required(VERSION 3.13)

# pull in SDK (must be before project)
message(STATUS "importing pico sdk: $ENV{PICO_SDK_PATH}\\external\\pico_sdk_import.cmake")
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
message(STATUS "importing pico extras: $ENV{PICO_EXTRAS_PATH}\\external\\pico_extras_import.cmake")
include($ENV{PICO_EXTRAS_PATH}/external/pico_extras_import.cmake)

# initialize project
project(spaceY-RFW C CXX ASM)

# set standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

#set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

# initialize the SDK
pico_sdk_init()


add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        )


if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()

add_executable(${PROJECT_NAME} main.cpp)

# pull in includes
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(spaceY-RFW pico_stdlib hardware_gpio)

pico_enable_stdio_usb(spaceY-RFW 1)
pico_enable_stdio_uart(spaceY-RFW 1)

pico_add_extra_outputs(spaceY-RFW)
