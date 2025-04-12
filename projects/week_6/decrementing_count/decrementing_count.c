// Embarcatech 2025 - "Countdown timer with event logging via interrupt" --- Filipe Alves de Sousa

#include <stdio.h>                      // Includes standard library for input/output functions (e.g., printf)
#include "pico/stdlib.h"                // Includes standard functions for Pico board, such as initialization and delay
#include "pico/time.h"                  // Includes timer utilities for time-related functions
#include "hardware/i2c.h"               // Includes functions for I2C communication (used by OLED display)
#include "hardware/gpio.h"              // Includes GPIO functions for pin control and interrupt handling
#include "inc/ssd1306.h"                // Includes declarations and definitions to control the OLED SSD1306 display
#include <string.h>                     // Includes functions for string manipulation (e.g., memset)

// Pin definitions for buttons and I2C (OLED display)
#define BUTTON_A 5                      // Pin for Button A, used to restart the countdown
#define BUTTON_B 6                      // Pin for Button B, used to count clicks during countdown

#define I2C_PORT i2c1                   // Define I2C port to be used
#define SDA_PIN 14                      // Pin for I2C data (SDA)
#define SCL_PIN 15                      // Pin for I2C clock (SCL)

#define DEBOUNCE_TIME_MS 300            // Debounce time in milliseconds to avoid button bouncing effects

// Global variables for countdown and click tracking
volatile int counter = 9;               // Countdown starting value
volatile int button_b_clicks = 0;       // Tracks the number of times Button B is clicked during the countdown
volatile bool active = false;           // Indicates whether countdown is active
volatile bool update_display = false;   // Indicates if the display needs to be updated

// Buffer and rendering area for the OLED display
uint8_t oled_buffer[ssd1306_buffer_length];  // Buffer to hold display data
struct render_area oled_area = {
    .start_column = 0,                  // Start column for rendering
    .end_column = ssd1306_width - 1,   // End column for rendering (width of the display)
    .start_page = 0,                    // Start page for rendering (each page contains 8 pixel rows)
    .end_page = ssd1306_n_pages - 1    // End page for rendering (total pages of the display)
};

// Variables for debounce timing
absolute_time_t last_button_a_time = { 0 };    // Tracks last time Button A was pressed
absolute_time_t last_button_b_time = { 0 };    // Tracks last time Button B was pressed

// Updates the OLED display with the current counter value and Button B click count
void update_oled() {
    memset(oled_buffer, 0, sizeof(oled_buffer)); // Clears the display buffer
    char msg[40];                                // Buffer for message formatting
    sprintf(msg, "Counter: %d", counter);        // Formats the counter value into the message
    ssd1306_draw_string(oled_buffer, 5, 10, msg); // Draws the counter message at specified position on the display
    sprintf(msg, "Clicks B: %d", button_b_clicks); // Formats the Button B click count into the message
    ssd1306_draw_string(oled_buffer, 5, 30, msg); // Draws the click count message below the counter message
    sprintf(msg, "restart A");                 // Adds instruction to restart the process
    ssd1306_draw_string(oled_buffer, 5, 50, msg); // Draws the restart message on the last line
    calculate_render_area_buffer_length(&oled_area); // Recalculates the render area
    render_on_display(oled_buffer, &oled_area);    // Renders the buffer content onto the OLED display
}

// GPIO interrupt callback function for button presses
void gpio_callback(uint gpio, uint32_t events) {
    absolute_time_t now = get_absolute_time(); // Gets the current time
    if (gpio == BUTTON_A && (events & GPIO_IRQ_EDGE_FALL)) { // Checks if Button A was pressed
        if (absolute_time_diff_us(last_button_a_time, now) > DEBOUNCE_TIME_MS * 1000) { // Debounce logic for Button A
            counter = 9;                          // Resets the counter to 9
            button_b_clicks = 0;                  // Resets the Button B click count
            active = true;                        // Activates the countdown
            update_display = true;                // Flags the display for updating
            last_button_a_time = now;             // Updates the last press time for Button A
        }
    }
    if (gpio == BUTTON_B && (events & GPIO_IRQ_EDGE_FALL)) { // Checks if Button B was pressed
        if (active && (absolute_time_diff_us(last_button_b_time, now) > DEBOUNCE_TIME_MS * 1000)) { // Debounce logic for Button B
            button_b_clicks++;                    // Increments the Button B click count
            update_display = true;                // Flags the display for updating
            last_button_b_time = now;             // Updates the last press time for Button B
        }
    }
}

// Timer callback function triggered every 1000 milliseconds (1 second)
bool timer_callback(repeating_timer_t* rt) {
    if (active) {                              // Checks if countdown is active
        if (counter > 0) {                     // If counter is greater than 0
            counter--;                         // Decrements the counter
        }
        else {                               // Otherwise
            active = false;                    // Deactivates the countdown
        }
        update_display = true;                 // Flags the display for updating
    }
    return true;                               // Keeps the timer active
}

int main() {
    stdio_init_all();                         // Initializes standard I/O for debug messages

    // Initializes the I2C communication for OLED display
    i2c_init(I2C_PORT, ssd1306_i2c_clock * 1000); // Sets the I2C clock speed
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);   // Configures the SDA pin for I2C functionality
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);   // Configures the SCL pin for I2C functionality
    gpio_pull_up(SDA_PIN);                       // Activates pull-up resistor for SDA pin
    gpio_pull_up(SCL_PIN);                       // Activates pull-up resistor for SCL pin

    // Initializes the Button A and Button B pins as input with pull-up resistors
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);

    // Configures the GPIO interrupt callback for buttons
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    gpio_set_irq_enabled(BUTTON_B, GPIO_IRQ_EDGE_FALL, true);

    // Initializes the OLED display
    ssd1306_init();                          // Sends initialization commands to the OLED
    update_oled();                           // Updates the OLED with initial values

    // Configures a repeating timer to trigger every 1000 milliseconds
    repeating_timer_t timer;
    add_repeating_timer_ms(1000, timer_callback, NULL, &timer);

    // Main loop: continuously checks for display updates
    while (true) {
        if (update_display) {               // If the display needs updating
            update_oled();                  // Updates the OLED display
            update_display = false;         // Resets the update flag
        }
        sleep_ms(50);                       // Sleep for 50 milliseconds to prevent excessive looping
    }

    return 0;                               // Return statement, not usually reached due to infinite loop
}
