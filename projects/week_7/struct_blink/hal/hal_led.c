// hal/hal_led.c - Hardware Abstraction Layer for the LED

#include "led_embutido.h"  // Hardware driver interface
#include "hal_led.h"       // Public HAL interface

/**
 * @brief Turns on the LED
 * @note Abstraction independent of the specific hardware
 */
inline void hal_led_turn_on(void)
{
    driver_set_state(true);  // Uses the driver function to turn on
}

/**
 * @brief Turns off the LED
 * @note Abstraction independent of the specific hardware
 */
inline void hal_led_turn_off(void)
{
    driver_set_state(false);  // Uses the driver function to turn off
}

/**
 * @brief Sets the LED state based on the parameter
 * @param on true to turn on, false to turn off
 */
inline void hal_led_set_state(bool on)
{
    on ? hal_led_turn_on() : hal_led_turn_off();
}

/**
 * @brief Toggles the current LED state (from on to off or vice versa)
 * @return New state of the LED after toggling
 */
inline bool hal_led_toggle(void)
{
    bool current = !driver_get_state();  // Gets and inverts the current state
    driver_set_state(current);          // Applies the new state
    return current;
}

/**
 * @brief Blinks the LED with a defined interval (blocking function)
 * @param ms Time in milliseconds for each state (on/off)
 * @note This function blocks execution during delays
 */
void hal_led_blink_delay(uint32_t ms)
{
    hal_led_turn_on();   // Turns on the LED
    sleep_ms(ms);        // Keeps it on for the specified time
    hal_led_turn_off();  // Turns off the LED
    sleep_ms(ms);        // Keeps it off for the specified time
}

/**
 * @brief Initializes the LED subsystem
 * @return 0 on success, error code on failure
 */
inline int hal_led_init(void)
{
    return driver_init();  // Delegates initialization to the driver
}
