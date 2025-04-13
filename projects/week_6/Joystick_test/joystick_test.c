// Embarcatech, April 2025 - "Joystick reader" --- Author: Filipe Alves de Sousa
// Reads the digitally converted values of the joystick from the BitDogLab.
// The values can be displayed on the terminal and on an OLED display.
//----------------------------------------------------------------------------------

#include <stdio.h>             // Standard library for input/output functions, e.g., printf().
#include <string.h>            // String manipulation library for handling strings and arrays.
#include "pico/stdlib.h"       // Standard functions for Raspberry Pi Pico board, like initialization and delay.
#include "hardware/adc.h"      // Library for controlling Analog-to-Digital Converter (ADC) functionality on RP2040.
#include "hardware/gpio.h"     // Library for GPIO (General-Purpose Input/Output) pin control and functions.
#include "hardware/i2c.h"      // Library for communication using I2C protocol.
#include "inc/ssd1306.h"       // Library for controlling the OLED display SSD1306.


// === CONFIGURATIONS ===
// Define GPIO pins and parameters for I2C and joystick control.

#define SDA_PIN 14               // GPIO pin for I2C data (SDA).
#define SCL_PIN 15               // GPIO pin for I2C clock (SCL).
#define I2C_PORT i2c1            // Defines the I2C port to be used (I2C1).
#define I2C_SPEED 100000         // I2C communication speed set to 100 kHz.

#define VRX_PIN 26               // GPIO pin for the joystick X-axis ADC input.
#define VRY_PIN 27               // GPIO pin for the joystick Y-axis ADC input.
#define JOY_SW  22               // GPIO pin for the joystick button (switch).

#define ADC_CH_X 0               // ADC channel for the X-axis.
#define ADC_CH_Y 1               // ADC channel for the Y-axis.

// Buffer and rendering area for the OLED display.
uint8_t oled_buffer[ssd1306_buffer_length]; // Buffer to store data for rendering on the OLED display.
struct render_area oled_area = {
    .start_column = 0,                  // Starting column of the rendering area.
    .end_column = ssd1306_width - 1,    // Ending column (covers the full width of the display).
    .start_page = 0,                    // Starting page (each page represents 8 vertical pixels).
    .end_page = ssd1306_n_pages - 1     // Ending page (covers the total height of the display).
};


// === FUNCTION: Initialize I2C and OLED display ===
// This function configures the I2C communication and initializes the OLED display.
bool setup_display()
{
    i2c_init(I2C_PORT, I2C_SPEED);          // Initializes the I2C communication with the specified speed.
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C); // Configures the SDA pin for I2C functionality.
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C); // Configures the SCL pin for I2C functionality.
    gpio_pull_up(SDA_PIN);                  // Activates the pull-up resistor for the SDA pin.
    gpio_pull_up(SCL_PIN);                  // Activates the pull-up resistor for the SCL pin.
    sleep_ms(200);                          // Waits for 200 milliseconds to stabilize communication.

    ssd1306_init();                         // Initializes the OLED display using the SSD1306 library.

    memset(oled_buffer, 0, sizeof(oled_buffer)); // Clears the OLED display buffer (sets all pixels to off).
    ssd1306_draw_string(oled_buffer, 0, 0, "Display OK!"); // Draws "Display OK!" message at the top of the OLED display.
    calculate_render_area_buffer_length(&oled_area); // Recalculates the buffer length for the specified rendering area.
    render_on_display(oled_buffer, &oled_area); // Renders the buffer content onto the OLED display.
    sleep_ms(1000);                          // Waits for 1000 milliseconds to display the message.
    return true;                             // Returns true indicating the display was successfully initialized.
}


// === FUNCTION: Initialize the joystick ===
// This function configures the GPIO pins and ADC channels for the joystick.
void setup_joystick()
{
    adc_init();                         // Initializes the ADC module.
    adc_gpio_init(VRX_PIN);             // Configures the GPIO pin for joystick X-axis ADC input.
    adc_gpio_init(VRY_PIN);             // Configures the GPIO pin for joystick Y-axis ADC input.
    gpio_init(JOY_SW);                  // Initializes the GPIO pin for the joystick button (switch).
    gpio_set_dir(JOY_SW, GPIO_IN);      // Configures the button pin as an input.
    gpio_pull_up(JOY_SW);               // Activates the pull-up resistor for the button pin to prevent floating values.
}


// === FUNCTION: Read joystick axis values ===
// This function reads the joystick's X and Y axes values using ADC channels.
void joystick_read_axis(uint16_t *eixo_x, uint16_t *eixo_y)
{
    adc_select_input(ADC_CH_X);         // Selects the ADC channel for the X-axis.
    sleep_us(5);                        // Waits for 5 microseconds to stabilize the reading.
    *eixo_x = adc_read();               // Reads the value from the X-axis ADC channel.

    adc_select_input(ADC_CH_Y);         // Selects the ADC channel for the Y-axis.
    sleep_us(5);                        // Waits for 5 microseconds to stabilize the reading.
    *eixo_y = adc_read();               // Reads the value from the Y-axis ADC channel.
}


// === FUNCTION: Display values on OLED display ===
// This function displays the joystick values (X, Y, button state) on the OLED screen.
void oled_display_values(uint16_t eixo_x, uint16_t eixo_y, uint8_t botao)
{
    memset(oled_buffer, 0, sizeof(oled_buffer)); // Clears the OLED buffer before rendering new data.

    char linha1[22], linha2[22], linha3[22], linha4[22]; // Buffers to store messages for display.
    snprintf(linha1, sizeof(linha1), "Joystick test:");  // Formats the title message.
    snprintf(linha2, sizeof(linha2), "X: %d", eixo_x);   // Formats the X-axis value message.
    snprintf(linha3, sizeof(linha3), "Y: %d", eixo_y);   // Formats the Y-axis value message.
    snprintf(linha4, sizeof(linha4), "Button: %s", botao ? "on 1" : "off 0"); // Formats the button state message.

    ssd1306_draw_string(oled_buffer, 0, 0, linha1);  // Draws the title message at the top of the OLED display.
    ssd1306_draw_string(oled_buffer, 0, 20, linha2); // Draws the X-axis message below the title.
    ssd1306_draw_string(oled_buffer, 0, 35, linha3); // Draws the Y-axis message below the X-axis.
    ssd1306_draw_string(oled_buffer, 0, 50, linha4); // Draws the button state message below the Y-axis.

    calculate_render_area_buffer_length(&oled_area); // Recalculates the buffer length for the specified rendering area.
    render_on_display(oled_buffer, &oled_area); // Renders the buffer content onto the OLED display.
}


// === GENERAL SETUP ===
// Configures the GPIO pins and initializes both joystick and OLED display.
void setup()
{
    stdio_init_all();                // Initializes standard I/O for debugging via serial communication.
    setup_joystick();                // Calls function to set up the joystick pins and ADC channels.
    if (!setup_display()) {          // Calls function to initialize the OLED display.
        printf("Error initializing display\n"); // Prints error message if display initialization fails.
    }
}


// === MAIN FUNCTION ===
// The main loop reads joystick values and updates both the serial monitor and OLED display.
int main()
{
    uint16_t x = 0, y = 0;           // Variables to hold X and Y axes values of the joystick.
    uint8_t botao = 0;               // Variable to hold the state of the joystick button.

    setup();                         // Calls the general setup function.
    printf("Starting joystick reading\n"); // Prints the start message to the serial monitor.

    while (1)                        // Infinite loop to continuously read and display joystick values.
    {
        joystick_read_axis(&x, &y);  // Reads the X and Y axes values of the joystick.
        botao = !gpio_get(JOY_SW);   // Reads the button state (active-low logic, so value is inverted).

        printf("X: %d, Y: %d, Button: %s\n", x, y, botao ? "ON 1" : "OFF 0"); // Prints joystick values to serial monitor.

        oled_display_values(x, y, botao); // Updates the OLED display with joystick values.

        sleep_ms(500);               // Waits for 500 milliseconds before repeating the loop.
    }
}
