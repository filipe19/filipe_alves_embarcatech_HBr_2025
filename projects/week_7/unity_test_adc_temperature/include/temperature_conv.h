// Embarcatech, April 2025 - RP2040 Internal Temperature Sensor Header
// Author: Filipe Alves de Sousa
/* ========================================================================
   
    This header defines the interface for converting RP2040 internal temperature
    sensor ADC readings to Celsius degrees.
    
    Key Features:
    - Conversion formula based on RP2040 datasheet specifications
    - Pre-calculated constants for optimal performance
    - 12-bit ADC resolution support
    ======================================================================== */

    #pragma once  // Ensures single inclusion of this header file

    #include <stdint.h>  // Standard integer types (uint16_t)
    
    // Sensor and ADC Configuration Constants
    #define VREF 3.3f             // Reference voltage (3.3V for Pico)
    #define ADC_RESOLUTION 4095.0f  // Maximum value for 12-bit ADC (2^12 - 1)
    
    // Temperature Sensor Characteristics (from RP2040 datasheet)
    #define TEMP_AT_27C 0.706f      // Voltage output at 27°C (calibration point)
    #define TEMP_COEFFICIENT (-0.001721f)  // Temperature coefficient (V/°C)
    
    /**
     * @brief Converts ADC reading to Celsius temperature
     * 
     * @param adc_val 12-bit ADC reading (0-4095)
     * @return float Temperature in degrees Celsius
     * 
     * @note Implements the RP2040-specific conversion formula:
     *       Temperature (°C) = 27 - (V_sensor - 0.706) / 0.001721
     *       Where V_sensor = adc_val × (3.3V / 4095)
     * 
     * @warning Input values above 4095 will be clamped to 4095
     * 
     * @example Basic usage:
     * @code
     * uint16_t reading = adc_read();
     * float temp = adc_to_celsius(reading);
     * @endcode
     */
    float adc_to_celsius(uint16_t adc_val);