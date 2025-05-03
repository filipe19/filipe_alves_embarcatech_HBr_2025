# **Internal Temperature Reader with ADC for Raspberry Pi Pico W**
This project demonstrates how to use the built-in temperature sensor in the RP2040 microcontroller of the Raspberry Pi Pico W, reading the value through the internal 12-bit ADC and converting the output to degrees Celsius based on the official documentation's equation.

## Overview
The RP2040 includes an internal temperature sensor connected to ADC channel 4, where the voltage varies linearly with temperature. The converted value can be used for thermal monitoring or control in embedded systems.

## This project includes:

ADC value to Celsius conversion

Function float adc_to_celsius(uint16_t adc_val);

Unit tests using Unity Test Framework

Modular and reusable structure

## **Conversion Equation**
The official equation from the RP2040 datasheet to convert voltage to temperature is:

r
Copiar
Editar
T(°C) = 27 - (V_ADC - 0.706) / 0.001721
Where:

V_ADC = (adc_val * 3.3) / 4095

0.706 V is the typical output at 27°C

0.001721 V/°C is the temperature-voltage slope

## **Project Structure**
pgsql
Copiar
Editar
rp2040_adc_temp_sensor/
├── src/
│   └── temperature_conv.c         # Conversion implementation
├── include/
│   └── temperature_conv.h         # Conversion function header
├── tests/
│   └── test_temperature_conv.c    # Unit tests with Unity
├── lib_unity_src/
│   └── unity.c
│   └── unity.h
│   └── unity_internals.h
├── CMakeLists.txt                 # Build configuration
└── README.md                      # This guide

## **Unit Tests (Unity Framework)**
Unit tests were implemented to validate the accuracy of the adc_to_celsius() conversion function using simulated ADC readings.

## Included tests:

 Calibration point (27°C)
 Typical value (20°C)
 Higher temperature (38°C)
 Lower temperature (-8°C)

## **Test Output Example**
mathematica
Copiar
Editar
=== Starting Temperature Conversion Tests ===

[1/4] Testing reference point (27°C)... PASS
[2/4] Testing typical value (20°C)... PASS
[3/4] Testing higher temperature (~38.48°C)... PASS
[4/4] Testing lower temperature (~-8.13°C)... PASS

=== All tests completed successfully ===

## How to Use
## **Prerequisites**
Raspberry Pi Pico W
Pico SDK
CMake ≥ 3.13
ARM Toolchain (e.g., arm-none-eabi)

## **Build Steps:**
bash
Copiar
Editar
git clone https://github.com/your-username/rp2040_adc_temp_sensor.git
cd rp2040_adc_temp_sensor
export PICO_SDK_PATH=/path/to/pico-sdk
mkdir build && cd build
cmake ..
make
Run Unit Tests
bash
Copiar
Editar
ctest -V

## **Practical Applications:**
Embedded temperature monitoring
Fan and thermal control
IoT projects using internal sensors
Hands-on learning about ADCs

## **References:**
RP2040 Datasheet - Section 4.9.5: Temperature Sensor
Unity Test Framework


## **System Behavior Images**
Below are screenshots and photos demonstrating the system in action:

### **The board during testing**  
![sctruct_blink](https:)  
_Photo of the BitDogLab board._

### **screenshot during testing using VSCode – compiling and running**  
![vscode_blink](https://github.com/user-attachments/assets/872)  
_Screenshot of the program running within the VS Code environment._


## **Contributions**
Feel free to:
Report bugs
Open feature requests
Contribute new test cases

## **License**
MIT License - see the LICENSE file for details.