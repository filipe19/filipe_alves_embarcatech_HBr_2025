# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initializes the Raspberry Pi Pico SDK
include(pico_sdk_import.cmake)

project(joystick_test C CXX ASM)

pico_sdk_init()

# Adds the project's source file and OLED display library
add_executable(joystick_test 
    joystick_test.c
    inc/ssd1306_i2c.c
)

pico_set_program_name(joystick_test "joystick_test")
pico_set_program_version(joystick_test "0.1")

# Enables USB output (for debugging)
pico_enable_stdio_usb(joystick_test 1)

# Standard libraries
target_link_libraries(joystick_test pico_stdlib hardware_i2c hardware_adc hardware_gpio)

# Includes the current directory
target_include_directories(joystick_test PRIVATE ${CMAKE_CURRENT_LIST_DIR})

pico_add_extra_outputs(joystick_test)
