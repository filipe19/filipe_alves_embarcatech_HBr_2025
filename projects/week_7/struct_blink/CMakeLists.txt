# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# Specify the minimum required version of CMake to ensure compatibility
cmake_minimum_required(VERSION 3.13)

# Configure language standards (C11 and C++17)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
# Generate a compilation commands file for analysis tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# === Specific settings for the VS Code Extension ===
# (better to keep this section intact for compatibility with the extension)
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})  # Home on Windows
else()
    set(USERHOME $ENV{HOME})         # Home on Unix-like systems
endif()
set(sdkVersion 2.1.1)               # SDK version
set(toolchainVersion 14_2_Rel1)     # Toolchain version
set(picotoolVersion 2.1.1)          # Picotool version
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})          # Includes settings from the VS Code extension
endif()
# ========================================================

# Specify the target board as Raspberry Pi Pico W
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Include the Pico SDK import script (must precede the project())
include(pico_sdk_import.cmake)

# Define the project name and supported languages
project(struct_blink 
    LANGUAGES C CXX ASM  # Explicitly declares C, C++, and Assembly as languages
)

# Initialize the Pico SDK
pico_sdk_init()

# Create the main executable with source files
add_executable(struct_blink 
    app/main.c            # Main application code
    drivers/led_embutido.c # Built-in LED driver
    hal/hal_led.c         # Hardware abstraction layer
)

# Define project metadata
pico_set_program_name(struct_blink "struct_blink")
pico_set_program_version(struct_blink "0.1")

# Configure default output (UART and USB disabled)
pico_enable_stdio_uart(struct_blink 0)  # 0 disables serial output
pico_enable_stdio_usb(struct_blink 0)   # 0 disables USB output

# Required standard libraries
target_link_libraries(struct_blink
    pico_stdlib          # Pico's standard library
)

# Include directories (adding explicit references to drivers and HAL directories)
target_include_directories(struct_blink PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include  # Public headers
    ${CMAKE_CURRENT_LIST_DIR}/drivers  # Driver headers
    ${CMAKE_CURRENT_LIST_DIR}/hal      # HAL headers
)

# Specific libraries for WiFi/CYW43 (Pico W)
target_link_libraries(struct_blink 
    pico_cyw43_arch       # CYW43 architecture
    pico_cyw43_arch_none  # OS-less implementation
)

# Generate additional outputs (.uf2, .hex, etc.)
pico_add_extra_outputs(struct_blink)
