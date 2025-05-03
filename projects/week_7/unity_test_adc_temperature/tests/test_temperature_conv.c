// Embarcatech, April 2025 - RP2040 Temperature Conversion Unit Tests
// Author: Filipe Alves de Sousa
// Unit tests for the adc_to_celsius() function using Unity framework
// Unit tests with detailed output for adc_to_celsius() function
// Tests cover reference point, typical values, and edge cases
//-----------------------------------------------------------------------------


// Include necessary libraries
#include "unity.h"              // Unity test framework
#include "temperature_conv.h"   // Header with conversion function
#include "pico/stdlib.h"        // Pico SDK standard library
#include <stdio.h>              // Standard I/O functions
#include <math.h>               // Math functions (for fabsf)

// Serial initialization with robust connection waiting
void init_serial() {
    stdio_init_all();           // Initialize all stdio (UART/USB)
    
    // Wait until serial connection is established
    while (!stdio_usb_connected()) {
        sleep_ms(100);          // Check every 100ms
    }
    sleep_ms(1000);             // Critical stabilization delay
}

// Required Unity setup function (can remain empty)
void setUp(void) {}

// Required Unity teardown function (can remain empty)
void tearDown(void) {}

// Helper function to calculate ADC value from voltage
uint16_t calculate_adc_value(float voltage) {
    // Convert voltage to 12-bit ADC value (0-4095)
    return (uint16_t)(voltage / VREF * ADC_RESOLUTION);
}

// Detailed test result printer (shows voltage and differences)
void print_detailed_result(const char* test_name, uint16_t adc, float expected, float actual) {
    printf("\n=== %s ===\n", test_name);                // Test name header
    printf("ADC Value: %u\n", adc);                     // Raw ADC value
    printf("Voltage: %.3f V\n", adc * VREF / ADC_RESOLUTION); // Calculated voltage
    printf("Expected: %.2f°C | Actual: %.2f°C\n", expected, actual); // Temperature comparison
    printf("Difference: %.2f°C\n", expected - actual);  // Delta between values
}

// Formatted test result printer (clean output with PASS/FAIL status)
void print_formatted_result(int test_num, const char* description, uint16_t adc, float expected, float actual) {
    // Determine test status based on tolerance
    const char* status = (fabsf(actual - expected) <= 0.5f ? "PASS" : "FAIL");
    
    // Aligned columns for readability
    printf("[%d/6] %-45s", test_num, description);
    printf("ADC: %-4u  Expected: %-7.2f°C  Actual: %-7.2f°C  %s\n", 
           adc, expected, actual, status);
}

/*----------------------------------------------------------
Test Cases (Each follows the same pattern):
1. Calculate expected voltage for target temperature
2. Convert to ADC value
3. Run conversion function
4. Print both detailed and formatted results
5. Assert with tolerance
----------------------------------------------------------*/

// 27°C calibration point test
void test_calibration_point() {
    uint16_t adc_val = calculate_adc_value(0.706f);  // Known 27°C voltage
    float temp = adc_to_celsius(adc_val);
    
    print_detailed_result("CALIBRATION POINT DETAILS", adc_val, 27.0f, temp);
    print_formatted_result(1, "Testing reference point (27°C)...", adc_val, 27.0f, temp);
    
    TEST_ASSERT_FLOAT_WITHIN(0.5f, 27.0f, temp);  // ±0.5°C tolerance
}

// 20°C typical value test
void test_typical_value() {
    // Calculate voltage for 20°C using sensor characteristics
    float voltage_20c = 0.706f + (27.0f - 20.0f) * (-0.001721f);
    uint16_t adc_val = calculate_adc_value(voltage_20c);
    float temp = adc_to_celsius(adc_val);
    
    print_detailed_result("TYPICAL VALUE DETAILS (20°C)", adc_val, 20.0f, temp);
    print_formatted_result(2, "Testing typical value (20°C)...", adc_val, 20.0f, temp);
    
    TEST_ASSERT_FLOAT_WITHIN(0.5f, 20.0f, temp);
}

// 38.48°C high temperature test
void test_higher_temperature() {
    float voltage_38c = 0.706f + (27.0f - 38.48f) * (-0.001721f);
    uint16_t adc_val = calculate_adc_value(voltage_38c);
    float temp = adc_to_celsius(adc_val);
    
    print_detailed_result("HIGH TEMPERATURE DETAILS (38.48°C)", adc_val, 38.48f, temp);
    print_formatted_result(3, "Testing higher temperature (~38.48°C)...", adc_val, 38.48f, temp);
    
    TEST_ASSERT_FLOAT_WITHIN(0.5f, 38.48f, temp);
}

// -8.13°C low temperature test
void test_lower_temperature() {
    float voltage_neg8c = 0.706f + (27.0f - (-8.13f)) * (-0.001721f);
    uint16_t adc_val = calculate_adc_value(voltage_neg8c);
    float temp = adc_to_celsius(adc_val);
    
    print_detailed_result("LOW TEMPERATURE DETAILS (-8.13°C)", adc_val, -8.13f, temp);
    print_formatted_result(4, "Testing lower temperature (~-8.13°C)...", adc_val, -8.13f, temp);
    
    TEST_ASSERT_FLOAT_WITHIN(0.5f, -8.13f, temp);
}

// Minimum ADC value (0) test
void test_min_adc_value() {
    uint16_t adc_min = 0;  // Minimum possible ADC reading
    float expected_min = 27.0f - ((0.0f - TEMP_AT_27C) / TEMP_COEFFICIENT);
    float actual_min = adc_to_celsius(adc_min);
    
    print_detailed_result("MINIMUM ADC VALUE DETAILS", adc_min, expected_min, actual_min);
    print_formatted_result(5, "Testing minimum ADC value (0)...", adc_min, expected_min, actual_min);
    
    TEST_ASSERT_FLOAT_WITHIN(1.0f, expected_min, actual_min);  // Wider tolerance for extremes
}

// Maximum ADC value (4095) test
void test_max_adc_value() {
    uint16_t adc_max = 4095;  // Maximum possible ADC reading
    float expected_max = 27.0f - ((VREF - TEMP_AT_27C) / TEMP_COEFFICIENT);
    float actual_max = adc_to_celsius(adc_max);
    
    print_detailed_result("MAXIMUM ADC VALUE DETAILS", adc_max, expected_max, actual_max);
    print_formatted_result(6, "Testing maximum ADC value (4095)...", adc_max, expected_max, actual_max);
    
    TEST_ASSERT_FLOAT_WITHIN(1.0f, expected_max, actual_max);
}

// Main test runner
int main() {
    init_serial();  // Initialize communication
    
    // Print test configuration header
    printf("\n===== TEMPERATURE SENSOR TEST =====\n");
    printf("VREF: %.1fV | ADC Resolution: %.0f\n", VREF, ADC_RESOLUTION);
    printf("Voltage @27°C: %.3fV\n\n", TEMP_AT_27C);
    printf("\n=== Starting Temperature Conversion Tests ===\n");
    
    // Start Unity test framework
    UNITY_BEGIN();
    
    // Execute all test cases
    RUN_TEST(test_calibration_point);
    RUN_TEST(test_typical_value);
    RUN_TEST(test_higher_temperature);
    RUN_TEST(test_lower_temperature);
    RUN_TEST(test_min_adc_value);
    RUN_TEST(test_max_adc_value);
    
    // Cleanup and exit
    printf("\n===== TEST COMPLETE =====\n");
    fflush(stdout);  // Ensure all output is flushed
    
    return UNITY_END();  // Finalize Unity tests
}