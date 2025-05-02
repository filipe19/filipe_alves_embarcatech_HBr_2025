// drivers/led_embutido.h - Driver interface for the built-in LED on the Pico W

#ifndef DRIVER_LED_H
#define DRIVER_LED_H

#include <stdbool.h>  // For the bool type

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes the LED hardware
 * @return 0 on success, negative error code on failure
 * @note Must be called before any other driver function
 */
int driver_init(void);

/**
 * @brief Controls the state of the built-in LED
 * @param state true to turn the LED on, false to turn it off
 * @warning Requires that driver_init() has been successfully called
 */
void driver_set_state(bool state);

/**
 * @brief Retrieves the current state of the LED
 * @return true if the LED is on, false if it is off
 */
bool driver_get_state(void);

/**
 * @brief Toggles the current state of the LED
 * @return New state of the LED after toggling
 */
bool driver_toggle(void);

#ifdef __cplusplus
}
#endif

#endif // DRIVER_LED_H
