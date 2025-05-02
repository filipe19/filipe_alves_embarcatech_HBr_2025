// drivers/led_embutido.c - Driver for the built-in LED on the Raspberry Pi Pico W

// Header file inclusion
#include "pico/cyw43_arch.h"  // Low-level API for hardware control of WiFi/CYW43
#include "led_embutido.h"     // Public interface of the driver

// Variable to track the current LED state
static bool led_state = false;

/**
 * @brief Sets the state of the built-in LED
 * @param state true to turn the LED on, false to turn it off
 * @note Inline function for maximum efficiency in frequent operations
 * @warning Requires the CYW43 subsystem to be initialized
 */
inline void driver_set_state(bool state) 
{
    led_state = state;  // Stores the current state
    // Controls the GPIO pin of the LED using the CYW43 API
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, state);
}

/**
 * @brief Initializes the LED subsystem
 * @return 0 on success, negative error code on failure
 * @note Performs the necessary CYW43 hardware initialization for the LED
 */
inline int driver_init() 
{
    int result = cyw43_arch_init();  // Initializes the CYW43 subsystem
    if (result == 0) {
        driver_set_state(false);  // Ensures the LED starts in the off state
    }
    return result;
}

/**
 * @brief Retrieves the current state of the LED
 * @return true if the LED is on, false if off
 */
inline bool driver_get_state(void)
{
    return led_state;
}

/**
 * @brief Toggles the state of the LED
 * @return The new state of the LED after toggling
 */
inline bool driver_toggle(void)
{
    bool new_state = !led_state;
    driver_set_state(new_state);
    return new_state;
}
