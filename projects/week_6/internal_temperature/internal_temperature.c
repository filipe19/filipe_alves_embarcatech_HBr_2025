// Embarcatech, April 2025 - "RP2040 Internal Temperature Reader"
// Author: Filipe Alves de Sousa
// This program reads the internal temperature sensor of the Raspberry Pi Pico (RP2040)
// and displays the temperature in Celsius on both the serial terminal and an OLED display.
//----------------------------------------------------------------------------------------------

#include <stdio.h>              // Provides standard input/output functions like printf()
#include <string.h>            // Includes functions for memory and string operations (e.g., memset, snprintf)
#include "pico/stdlib.h"       // Includes Pico SDK utilities (GPIO, sleep, etc.)
#include "hardware/adc.h"      // Provides functions to interact with the ADC (Analog-to-Digital Converter)
#include "hardware/gpio.h"     // Enables configuration of GPIO pins
#include "hardware/i2c.h"      // Used for I2C communication setup and control
#include "inc/ssd1306.h"       // Custom OLED library to control the SSD1306 display via I2C

// === OLED DISPLAY CONFIGURATION ===
#define SDA_PIN 14             // Assigns GPIO 14 as the SDA line for I2C communication
#define SCL_PIN 15             // Assigns GPIO 15 as the SCL line for I2C communication
#define I2C_PORT i2c1          // Specifies the I2C1 hardware peripheral to be used
#define I2C_SPEED 100000       // Sets I2C communication speed to 100 kHz

// Buffer and rendering area for the OLED display
uint8_t oled_buffer[ssd1306_buffer_length];  // Defines a buffer to store image/text data before sending to display

// Specifies the screen area that should be updated when drawing content
struct render_area oled_area = {
    .start_column = 0,                        // First column to be drawn (leftmost pixel)
    .end_column = ssd1306_width - 1,          // Last column to be drawn (rightmost pixel)
    .start_page = 0,                          // First page (group of 8 vertical pixels) to draw
    .end_page = ssd1306_n_pages - 1           // Last page to be drawn (entire screen height)
};

// === FUNCTION: Initializes I2C and OLED display ===
bool setup_display()
{
    i2c_init(I2C_PORT, I2C_SPEED);            // Initializes the I2C port with the specified speed
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C); // Configures the SDA pin for I2C functionality
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C); // Configures the SCL pin for I2C functionality
    gpio_pull_up(SDA_PIN);                    // Enables internal pull-up resistor on SDA
    gpio_pull_up(SCL_PIN);                    // Enables internal pull-up resistor on SCL
    sleep_ms(200);                            // Waits 200 ms for hardware to stabilize

    ssd1306_init();                           // Initializes the OLED display (sends setup commands)

    memset(oled_buffer, 0, sizeof(oled_buffer));     // Clears the display buffer (fills it with 0s)
    ssd1306_draw_string(oled_buffer, 0, 0, "Display OK!"); // Draws "Display OK!" at X=0, Y=0 on the buffer
    calculate_render_area_buffer_length(&oled_area); // Calculates the number of bytes to be sent to the display
    render_on_display(oled_buffer, &oled_area);      // Renders the buffer on the OLED screen
    sleep_ms(1000);                            // Displays the message for 1 second
    return true;                               // Returns true to indicate successful initialization
}

// === FUNCTION: Initializes the internal temperature sensor ===
void setup_temp_sensor()
{
    adc_init();                                // Initializes the ADC peripheral
    adc_set_temp_sensor_enabled(true);         // Enables the internal temperature sensor
    adc_select_input(4);                       // Selects ADC input channel 4 (connected to internal sensor)
}

// === FUNCTION: Reads internal temperature from the RP2040 ===
float read_temperature()
{
    uint16_t raw = adc_read();                 // Reads the raw 12-bit value from the ADC

    const float conversion_factor = 3.3f / (1 << 12); // Converts raw value to voltage (3.3V / 4096)
    float voltage = raw * conversion_factor;   // Converts raw ADC value to actual voltage

    float temp = 27 - (voltage - 0.706) / 0.001721; // Uses formula from datasheet to convert voltage to temperature
    return temp;                                // Returns the temperature in Celsius
}

// === FUNCTION: Displays temperature on the OLED screen ===
void oled_display_temperature(float temp)
{
    memset(oled_buffer, 0, sizeof(oled_buffer));       // Clears the OLED buffer before drawing

    char linha1[22], linha2[22];                       // Buffers for holding text strings
    snprintf(linha1, sizeof(linha1), "internal temp:"); // Prepares the label string
    snprintf(linha2, sizeof(linha2), "%.2f C", temp);  // Formats the temperature value to two decimal places

    ssd1306_draw_string(oled_buffer, 0, 0, linha1);     // Draws the label on the display at Y=0
    ssd1306_draw_string(oled_buffer, 0, 30, linha2);    // Draws the temperature value below it at Y=30

    calculate_render_area_buffer_length(&oled_area);   // Calculates the area of the buffer to be sent
    render_on_display(oled_buffer, &oled_area);        // Sends the buffer content to be rendered on the OLED screen
}

// === FUNCTION: General setup ===
void setup()
{
    stdio_init_all();                          // Initializes USB serial communication (for printf)
    setup_temp_sensor();                       // Calls the function to set up the temperature sensor
    if (!setup_display()) {                    // Calls the function to set up the OLED display
        printf("Erro on display initialize!\n"); // Prints an error message if setup failed
    }
}

// === MAIN FUNCTION ===
int main()
{
    setup();                                   // Calls the general setup function
    printf("Initialize internal temperature read...\n"); // Prints start message to serial monitor

    while (1)                                  // Infinite loop (runs forever)
    {
        float temp = read_temperature();       // Reads the current internal temperature
        printf("internal temperature: %.2f C\n", temp); // Prints temperature to serial monitor
        oled_display_temperature(temp);        // Displays temperature on the OLED screen
        sleep_ms(1000);                        // Waits 1 second before reading again
    }
}
