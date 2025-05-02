// hal/hal_led.h - Hardware Abstraction Layer for LED control

#ifndef HAL_LED_H
#define HAL_LED_H

// Inclusion of the basic Pico header for standard types
#include "pico/stdlib.h"  // Provides basic definitions and uint32_t

// Protection for C++ compilation
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Blinks the LED with a defined interval (blocking function)
 * @param ms Time in milliseconds for each state (on/off)
 * @note This function blocks execution during delays
 */
void hal_led_blink_delay(uint32_t ms);

/**
 * @brief Turns off the LED
 */
void hal_led_turn_off(void);

/**
 * @brief Turns on the LED
 */
void hal_led_turn_on(void);

/**
 * @brief Sets the LED state
 * @param on true to turn on, false to turn off
 */
void hal_led_set_state(bool on);

/**
 * @brief Initializes the LED subsystem
 * @return 0 on success, error code on failure
 */
int hal_led_init(void);

// End of protection for C++
#ifdef __cplusplus
}
#endif

#endif // HAL_LED_H
