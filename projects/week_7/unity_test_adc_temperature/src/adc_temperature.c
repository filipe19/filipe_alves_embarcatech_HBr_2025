// Embarcatech, April 2025 - RP2040 Internal Temperature Reader
// Author: Filipe Alves de Sousa
// This program reads the internal temperature sensor of the Raspberry Pi Pico (RP2040)
// Includes ADC to Celsius conversion function and unit tests using Unity framework
//----------------------------------------------------------------------------------------------


/* ========================================================================
    Embarcatech, April 2025 - RP2040 Internal Temperature Reader
    Author: Filipe Alves de Sousa
    
    This module implements the internal temperature sensor reading and conversion
    for Raspberry Pi Pico (RP2040). Includes:
    - ADC to Celsius conversion function
    - Input validation
    - Optimized floating-point calculation
    ======================================================================== */

    #include "temperature_conv.h"  // Include corresponding header

    /**
     * @brief Converts 12-bit ADC reading to temperature in Celsius
     * 
     * @param adc_val Raw ADC reading (0-4095)
     * @return float Temperature in degrees Celsius
     * 
     * @details Implements the conversion formula:
     *          T = 27 - (V_sensor - 0.706)/0.001721
     *          Where V_sensor = (adc_val × 3.3V)/4095
     * 
     * @note Features:
     *       - Input validation (clamps values >4095)
     *       - Single-step floating point calculation
     *       - Factory calibrated at 27°C (±1°C accuracy)
     * 
     * @warning For best accuracy:
     *          - Use stable 3.3V reference
     *          - Allow sensor stabilization time
     */
    float adc_to_celsius(uint16_t adc_val) {
        // Input validation (protect against overflow)
        if (adc_val > ADC_RESOLUTION) {
            adc_val = ADC_RESOLUTION;  // Clamp to maximum valid value
        }
        
        /* Optimized single-step conversion:
         * 1. Convert ADC to voltage: (adc_val × 3.3V)/4095
         * 2. Subtract calibration voltage: (V - 0.706V)
         * 3. Apply temperature coefficient: /(-0.001721 V/°C)
         * 4. Subtract from calibration temp: 27°C - result
         */
        return 27.0f - (((adc_val * VREF / ADC_RESOLUTION) - TEMP_AT_27C) / TEMP_COEFFICIENT);
    }
    
    /* ============================== Implementation Notes ==============================
    1. Voltage Calculation:
       - RP2040 uses 12-bit ADC (0-4095) with 3.3V reference
       - Example: 875 → (875×3.3)/4095 ≈ 0.706V
    
    2. Temperature Calculation:
       - At 27°C: sensor outputs 0.706V
       - Coefficient: -1.721mV/°C (negative slope)
       - Formula rearranged for single-step computation
    
    3. Error Handling:
       - Input clamping prevents overflow
       - No division by zero risk (fixed coefficient)
    =================================================================================== */