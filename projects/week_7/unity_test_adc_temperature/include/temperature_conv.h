// Embarcatech, April 2025 - RP2040 Internal Temperature Sensor Header
// Author: Filipe Alves de Sousa
// This header defines the interface for converting RP2040 internal temperature
// sensor ADC readings to Celsius degrees.
//-----------------------------------------------------------------------------

#ifndef TEMPERATURE_CONVERTER_H
#define TEMPERATURE_CONVERTER_H

#include <stdint.h>  // For uint16_t type

/**
 * @brief Converts 12-bit ADC reading from RP2040 internal temperature sensor to Celsius
 * 
 * @details This function implements the conversion formula specified in the RP2040 datasheet:
 *          Temperature (°C) = 27 - (V_sensor - 0.706) / 0.001721
 *          Where:
 *          - V_sensor = adc_val × (3.3V / 4095)
 *          - 0.706V is the sensor output voltage at 27°C
 *          - -1.721mV/°C is the temperature coefficient
 * 
 * @note Important characteristics:
 *       - Uses 3.3V as ADC reference voltage (Vref)
 *       - Valid for 12-bit ADC readings (0-4095)
 *       - Accuracy is ±1°C according to datasheet
 *       - Sensor is factory calibrated at 27°C
 * 
 * @param adc_val 12-bit ADC reading (range 0-4095)
 * @return float Temperature in degrees Celsius
 * 
 * @example Example usage:
 * @code
 * uint16_t adc_reading = 875;  // ~0.706V reading
 * float temp = adc_to_celsius(adc_reading);  // Should be ~27.0°C
 * @endcode
 */
float adc_to_celsius(uint16_t adc_val);

#endif // TEMPERATURE_CONVERTER_H