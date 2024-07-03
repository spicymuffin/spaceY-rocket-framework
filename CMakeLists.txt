cmake_minimum_required(VERSION 3.13)

# pull in SDK (must be before project)
message(STATUS "importing pico sdk: $ENV{PICO_SDK_PATH}\\external\\pico_sdk_import.cmake")
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
# message(STATUS "importing pico extras: $ENV{PICO_EXTRAS_PATH}\\external\\pico_extras_import.cmake")
# include($ENV{PICO_EXTRAS_PATH}/external/pico_extras_import.cmake)

set(MAIN_EXECUTABLE_NAME RFW-main)
set(TEST_EXECUTABLE_NAME RFW-test)
set(LIB_NAME RFW-lib)

# initialize project
project(${MAIN_EXECUTABLE_NAME} C CXX ASM)
project(${TEST_EXECUTABLE_NAME} C CXX ASM)
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

# add main.cpp
add_executable(${MAIN_EXECUTABLE_NAME} main.cpp)

# add test.cpp
add_executable(${TEST_EXECUTABLE_NAME} test.cpp)

# add all .cpp files recursively in src
add_library(${LIB_NAME} STATIC ${SRC_FILES})

# pull in includes for main
target_include_directories(${MAIN_EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${MAIN_EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# pull in includes test
target_include_directories(${TEST_EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${TEST_EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# pull in includes for lib
target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# link libs for main
target_link_libraries(${MAIN_EXECUTABLE_NAME} pico_stdlib hardware_gpio hardware_i2c ${LIB_NAME})

# link libs for test
target_link_libraries(${TEST_EXECUTABLE_NAME} pico_stdlib hardware_gpio hardware_i2c ${LIB_NAME})

# link libs for lib
target_link_libraries(${LIB_NAME} pico_stdlib hardware_gpio hardware_i2c hardware_dma)

# something related to console output
pico_enable_stdio_usb(${MAIN_EXECUTABLE_NAME} 1)
pico_enable_stdio_uart(${MAIN_EXECUTABLE_NAME} 0)
pico_enable_stdio_usb(${TEST_EXECUTABLE_NAME} 1)
pico_enable_stdio_uart(${TEST_EXECUTABLE_NAME} 0)

# give uf2 files
pico_add_extra_outputs(${MAIN_EXECUTABLE_NAME})
pico_add_extra_outputs(${TEST_EXECUTABLE_NAME})
