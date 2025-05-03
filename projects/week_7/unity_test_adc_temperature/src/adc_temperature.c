// Embarcatech, April 2025 - RP2040 Internal Temperature Reader
// Author: Filipe Alves de Sousa
// This program reads the internal temperature sensor of the Raspberry Pi Pico (RP2040)
// Includes ADC to Celsius conversion function and unit tests using Unity framework
//----------------------------------------------------------------------------------------------

#include <stdint.h>

/**
 * @brief Converts ADC reading from RP2040 internal temperature sensor to Celsius
 * @param adc_val 12-bit ADC reading (0-4095)
 * @return Temperature in degrees Celsius
 */
float adc_to_celsius(uint16_t adc_val) {
    // Convert ADC value to voltage (0-3.3V range)
    // 4095.0f is used because it's a 12-bit ADC (2^12 - 1)
    float voltage = adc_val * 3.3f / 4095.0f;
    
    // Convert voltage to temperature using the RP2040-specific formula:
    // The sensor outputs ~0.706V at 27°C with a slope of -1.721mV/°C
    // Formula derived from: T = 27 - (V_sensor - 0.706) / 0.001721
    float temperature = 27.0f - (voltage - 0.706f) / 0.001721f;
    
    return temperature;
}

// Unit test section (using Unity framework)
#ifdef TEST
#include "unity.h"

#define ADC_VALUE_FOR_27C 875  // 0.706V corresponds to ~875 in 12-bit ADC (0.706/3.3*4095)

void setUp(void) {
    // Setup code (if needed) runs before each test
}

void tearDown(void) {
    // Cleanup code (if needed) runs after each test
}

void test_adc_to_celsius_27c(void) {
    // Test known value: 0.706V should give 27°C
    float result = adc_to_celsius(ADC_VALUE_FOR_27C);
    TEST_ASSERT_FLOAT_WITHIN(0.5f, 27.0f, result);  // Allowing ±0.5°C margin
}

void test_adc_to_celsius_other_values(void) {
    // Test another known value (example: 0.5V)
    uint16_t adc_val = (uint16_t)(0.5f / 3.3f * 4095.0f);
    float expected_temp = 27.0f - (0.5f - 0.706f) / 0.001721f;
    float result = adc_to_celsius(adc_val);
    TEST_ASSERT_FLOAT_WITHIN(0.5f, expected_temp, result);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_adc_to_celsius_27c);
    RUN_TEST(test_adc_to_celsius_other_values);
    return UNITY_END();
}
#endif