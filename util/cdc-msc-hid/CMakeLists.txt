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

if (NOT PICO_TINYUSB_PATH)
    if(DEFINED ENV{PICO_TINYUSB_PATH})
        set(PICO_TINYUSB_PATH $ENV{PICO_TINYUSB_PATH})
        message("Setting PICO_TINYUSB_PATH from environment ('${PICO_TINYUSB_PATH}')")
    elseif(DEFINED CMAKE_ROOT_LIST_DIR)
        set(PICO_TINYUSB_PATH ${CMAKE_ROOT_LIST_DIR}/lib/tinyusb)
        message("Setting PICO_TINYUSB_PATH from git submodule path ('${PICO_TINYUSB_PATH}')")
    else()
        set(PICO_TINYUSB_PATH ${CMAKE_CURRENT_LIST_DIR}/lib/tinyusb)
        message("Setting PICO_TINYUSB_PATH from git submodule path ('${PICO_TINYUSB_PATH}')")
    endif()
else()
    message("PICO_TINYUSB_PATH already set ('${PICO_TINYUSB_PATH}')")
endif()

find_package(Python3 COMPONENTS Interpreter)
execute_process(COMMAND ${Python3_EXECUTABLE} ${PICO_TINYUSB_PATH}/tools/get_deps.py rp2040)

# if (NOT PICO_PIO_USB_PATH)
#     if(DEFINED ENV{PICO_PIO_USB_PATH})
#         set(PICO_PIO_USB_PATH $ENV{PICO_PIO_USB_PATH})
#         message("Setting PICO_PIO_USB_PATH from environment ('${PICO_PIO_USB_PATH}')")
#     else()
#         set(PICO_PIO_USB_PATH ${CMAKE_CURRENT_LIST_DIR}/lib/Pico-PIO-USB)
#         message("Setting PICO_PIO_USB_PATH from git submodule path ('${PICO_PIO_USB_PATH}')")
#     endif()
# else()
#     message("PICO_PIO_USB_PATH already set ('${PICO_PIO_USB_PATH}')")
# endif()

#
# Pico SDK setup
#
set(PICO_BOARD pico_w)
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

#
# General Setup
#
set(FAMILY rp2040)
set(PROJECT cdc-msc-hid)
project(${PROJECT} C CXX ASM)
add_executable(${PROJECT})

#
# TinyUSB setup
#
include (${PICO_TINYUSB_PATH}/hw/bsp/family_support.cmake)
family_initialize_project(${PROJECT} ${CMAKE_CURRENT_LIST_DIR})
# family_add_pico_pio_usb(${PROJECT})


#
# Configure Soruces
#
file(GLOB_RECURSE FILES src/*.c src/*.cpp src/*.h src/*.hpp src/*.pio)
target_sources(${PROJECT} PUBLIC ${FILES})
target_include_directories(${PROJECT} PUBLIC 
    ${PICO_TINYUSB_PATH}/src
    ${PICO_TINYUSB_PATH}/hw
	${CMAKE_CURRENT_LIST_DIR}/src
	${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${PROJECT} PRIVATE 
    pico_stdlib
    pico_multicore
    hardware_pio
    hardware_dma
    hardware_uart
    hardware_flash
    tinyusb_device
    tinyusb_host
    tinyusb_board
    tinyusb_pico_pio_usb
)

# target_compile_options(${PROJECT} PUBLIC
#     -Wno-error=shadow
#     -Wno-error=cast-align
#     -Wno-error=cast-qual
#     -Wno-error=redundant-decls
#     -Wno-error=sign-conversion
#     -Wno-error=conversion
#     -Wno-error=sign-compare
#     -Wno-error=unused-function

#     -Wno-cast-qual
#     -Wno-cast-align
#     -Wno-sign-compare
#     -Wno-shadow
#     -Wno-redundant-decls
#     -Wno-unused-function
# )

family_configure_host_example(${PROJECT} noos)

if (DEFINED CMAKE_ROOT_LIST_DIR)
    add_custom_command(TARGET ${PROJECT} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_ROOT_LIST_DIR}/dist/util
    )
    add_custom_command(TARGET ${PROJECT} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_ROOT_LIST_DIR}/build/util/${PROJECT}/${PROJECT}.uf2
        ${CMAKE_ROOT_LIST_DIR}/dist/util/${PROJECT}.uf2
    )
endif()