// Embarcatech, April 2025
// --- Author: Filipe Alves de Sousa
// Modular code architecture
// Initializes the built-in LED on the Raspberry Pi Pico W and makes it blink indefinitely

// Include necessary headers
#include "pico/stdlib.h"  // Pico standard library for basic functions
#include "hal_led.h"      // Hardware abstraction interface for the LED

/**
 * @brief Main entry point of the application
 * 
 * @return int Status code (0 for success, negative for error)
 */
int main()
{
    // Initialize all standard Pico functionalities
    // (UART, GPIO, etc., as configured in CMake)
    stdio_init_all();

    // Initialize the LED subsystem via HAL
    // Returns non-zero if initialization fails
    if (hal_led_init() != 0) {
        // In real systems, it would be good to log the error before exiting
        return -1;  // Error code for initialization failure
    }

    // Main application loop
    while (true)
    {
        // Blinks the LED with a 500ms interval (on/off)
        // Blocking function - keeps time control internally
        hal_led_blink_delay(500);
    }

    // Never reached, but kept for completeness
    return 0;
}
