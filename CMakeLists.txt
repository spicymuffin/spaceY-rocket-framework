cmake_minimum_required(VERSION 3.13)

# pull in SDK (must be before project)
message(STATUS "importing pico sdk: $ENV{PICO_SDK_PATH}\\external\\pico_sdk_import.cmake")
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
# message(STATUS "importing pico extras: $ENV{PICO_EXTRAS_PATH}\\external\\pico_extras_import.cmake")
# include($ENV{PICO_EXTRAS_PATH}/external/pico_extras_import.cmake)

set(EXECUTABLE_NAME RFW-main)
set(LIB_NAME RFW-lib)

# initialize project
project(${EXECUTABLE_NAME} C CXX ASM)
project(${LIB_NAME} C CXX ASM)

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
        -Wno-unknown-pragmas
        )


if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
file(GLOB_RECURSE LIB_FILES "lib/*.cpp")

# add main.cpp
add_executable(${EXECUTABLE_NAME} main.cpp)

# add all .cpp files recursively in src
add_library(${LIB_NAME} STATIC ${SRC_FILES} ${LIB_FILES})

# pull in includes
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_link_libraries(${EXECUTABLE_NAME} pico_stdlib hardware_gpio hardware_i2c ${LIB_NAME})
target_link_libraries(${LIB_NAME} pico_stdlib hardware_gpio hardware_i2c hardware_dma)

pico_enable_stdio_usb(${EXECUTABLE_NAME} 1)
pico_enable_stdio_uart(${EXECUTABLE_NAME} 0)

pico_add_extra_outputs(${EXECUTABLE_NAME})
