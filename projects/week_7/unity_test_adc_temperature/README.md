# **Internal Temperature Reader with ADC for Raspberry Pi Pico W**

This project provides an efficient implementation of the RP2040 microcontroller’s internal temperature sensor. It reads the sensor value via the built-in 12-bit ADC and converts the output to degrees Celsius using the official equation provided in the documentation.

## **Overview**
The RP2040 features an internal temperature sensor connected to ADC channel 4. The sensor’s voltage varies linearly with temperature, making it useful for basic thermal monitoring in embedded applications.

## **Features**
- Accurate ADC-to-Celsius conversion  
- Function: `float adc_to_celsius(uint16_t adc_val);`  
- Unit tests using the **Unity Test Framework**  
- Modular and reusable structure  



### **Conversion Equation (from the RP2040 Datasheet)**
The official formula from the RP2040 datasheet for converting ADC voltage to temperature is:

```
T [°C] = 27 - (V_ADC - 0.706) / 0.001721
```


> **Note**: The formula provides an approximation. For precision applications, consider calibrating the sensor or using an external voltage reference.

Source: [RP2040 Datasheet – Raspberry Pi](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)

Where:  

- `V_ADC`: the voltage measured by the ADC.
- `0.706 V`: the typical sensor output voltage at 27°C.
- `0.001721 V/°C`: represents the temperature-voltage slope; the voltage change per degree Celsius.




## **Project Structure**
```
rp2040_adc_temp_sensor/
├── src/
│   └── temperature_conv.c         # Conversion implementation
├── include/
│   └── temperature_conv.h         # Conversion function header
├── tests/
│   └── test_temperature_conv.c    # Unit tests with Unity framework
├── lib_unity_src/
│   └── unity.c
│   └── unity.h
│   └── unity_internals.h
├── CMakeLists.txt                 # Build configuration
└── README.md                      # Documentation
```

## **Unit Tests (Unity Framework)**
Unit tests were implemented to validate the accuracy of the adc_to_celsius() conversion function using simulated ADC readings.

## Included tests:

 Calibration point (27°C)
 Typical value (20°C)
 Higher temperature (38°C)
 Lower temperature (-8°C)

## **Test Output Example**

```
=== Starting Temperature Conversion Tests ===

[1/4] Testing reference point (27°C)... PASS
[2/4] Testing typical value (20°C)... PASS
[3/4] Testing higher temperature (~38.48°C)... PASS
[4/4] Testing lower temperature (~-8.13°C)... PASS

=== All tests completed successfully ===

```

## How to Use
## **Prerequisites**

Raspberry Pi Pico W
Pico SDK
CMake ≥ 3.13
ARM Toolchain (e.g., arm-none-eabi)

## **Build Steps:**
```
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
```

## **Practical Applications:**
Embedded temperature monitoring;
Fan and thermal control;
IoT projects using internal sensors; and
Hands-on learning about ADCs.

## **References:**
RP2040 Datasheet - Section 4.9.5: Temperature Sensor; 
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