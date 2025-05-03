// Embarcatech, April 2025 - RP2040 Temperature Conversion Unit Tests
// Author: Filipe Alves de Sousa
// Unit tests for the adc_to_celsius() function using Unity framework
// Unit tests with detailed output for adc_to_celsius() function
// Tests cover reference point, typical values, and edge cases
//-----------------------------------------------------------------------------

#include "unity.h"
#include "temperature_conv.h"
#include "pico/stdlib.h"

// Test configuration constants
const float TEST_ADC_VREF = 3.3f;                          // Reference voltage
const float TEST_ADC_RANGE_MINUS_1 = 4095.0f;              // 12-bit ADC range (2^12 - 1)
const float TEST_ADC_CONVERSION_FACTOR = TEST_ADC_VREF / TEST_ADC_RANGE_MINUS_1;
const float TEST_TEMP_SENSOR_VOLTAGE_AT_27C = 0.706f;      // Factory calibration point
const float TEST_TEMP_SENSOR_SLOPE = 0.001721f;            // -1.721mV/°C

void setUp(void) {}
void tearDown(void) {}

/**
 * @brief Helper function to print test measurements
 */
void print_measurement_details(uint16_t adc_val, float expected_temp, float actual_temp) {
    float voltage = (float)adc_val * TEST_ADC_CONVERSION_FACTOR;
    printf("ADC Value: %u\n", adc_val);
    printf("Voltage: %.3fV\n", voltage);
    printf("Expected Temp: %.2f°C\n", expected_temp);
    printf("Actual Temp: %.2f°C\n", actual_temp);
    printf("Difference: %.2f°C\n\n", expected_temp - actual_temp);
}

void test_adc_to_celsius_near_reference_point(void) {
    uint16_t test_adc_input = 876;  // Near 27°C point
    
    float expected_voltage = (float)test_adc_input * TEST_ADC_CONVERSION_FACTOR;
    float expected_temp_c = 27.0f - (expected_voltage - TEST_TEMP_SENSOR_VOLTAGE_AT_27C) / TEST_TEMP_SENSOR_SLOPE;

    printf("\n[TEST 1] Testing near reference point (27°C)\n");
    printf("----------------------------------------\n");
    
    float actual_temp_c = adc_to_celsius(test_adc_input);
    print_measurement_details(test_adc_input, expected_temp_c, actual_temp_c);
    
    TEST_ASSERT_FLOAT_WITHIN(0.5f, expected_temp_c, actual_temp_c);
}

void test_adc_to_celsius_at_20C(void) {
    uint16_t test_adc_input = 891;  // Approx 20°C
    
    float expected_voltage = (float)test_adc_input * TEST_ADC_CONVERSION_FACTOR;
    float expected_temp_c = 27.0f - (expected_voltage - TEST_TEMP_SENSOR_VOLTAGE_AT_27C) / TEST_TEMP_SENSOR_SLOPE;

    printf("\n[TEST 2] Testing at approximately 20°C\n");
    printf("------------------------------------\n");
    
    float actual_temp_c = adc_to_celsius(test_adc_input);
    print_measurement_details(test_adc_input, expected_temp_c, actual_temp_c);
    
    TEST_ASSERT_FLOAT_WITHIN(0.5f, expected_temp_c, actual_temp_c);
}

void test_adc_to_celsius_higher_temp(void) {
    uint16_t test_adc_input = 850;  // Higher temp (~38.48°C)
    
    float expected_voltage = (float)test_adc_input * TEST_ADC_CONVERSION_FACTOR;
    float expected_temp_c = 27.0f - (expected_voltage - TEST_TEMP_SENSOR_VOLTAGE_AT_27C) / TEST_TEMP_SENSOR_SLOPE;

    printf("\n[TEST 3] Testing higher temperature (~38.48°C)\n");
    printf("--------------------------------------------\n");
    
    float actual_temp_c = adc_to_celsius(test_adc_input);
    print_measurement_details(test_adc_input, expected_temp_c, actual_temp_c);
    
    TEST_ASSERT_FLOAT_WITHIN(0.5f, expected_temp_c, actual_temp_c);
}

void test_adc_to_celsius_lower_temp(void) {
    uint16_t test_adc_input = 950;  // Lower temp (~-8.13°C)
    
    float expected_voltage = (float)test_adc_input * TEST_ADC_CONVERSION_FACTOR;
    float expected_temp_c = 27.0f - (expected_voltage - TEST_TEMP_SENSOR_VOLTAGE_AT_27C) / TEST_TEMP_SENSOR_SLOPE;

    printf("\n[TEST 4] Testing lower temperature (~-8.13°C)\n");
    printf("--------------------------------------------\n");
    
    float actual_temp_c = adc_to_celsius(test_adc_input);
    print_measurement_details(test_adc_input, expected_temp_c, actual_temp_c);
    
    TEST_ASSERT_FLOAT_WITHIN(0.5f, expected_temp_c, actual_temp_c);
}

int main(void) {
    stdio_init_all();
    sleep_ms(2000);  // Wait for serial connection

    printf("\n=== Starting Temperature Conversion Tests ===\n");
    printf("==========================================\n\n");

    UNITY_BEGIN();
    RUN_TEST(test_adc_to_celsius_near_reference_point);
    RUN_TEST(test_adc_to_celsius_at_20C);
    RUN_TEST(test_adc_to_celsius_higher_temp);
    RUN_TEST(test_adc_to_celsius_lower_temp);
    
    printf("\n=== All tests completed ===\n");
    return UNITY_END();
}