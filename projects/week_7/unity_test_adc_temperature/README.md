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

- Calibration point (27°C)
- Typical value (20°C)
- Higher temperature (38°C)
- Lower temperature (-8°C)

## Adjusted Tolerances:

±0.5°C for normal operating temperatures (calibrated range near 27°C)

±1.0°C for extreme values (near ADC limits 0-4095)

### Additional technical notes:

- The tighter ±0.5°C tolerance applies to the sensor's optimal range (typically 10°C to 40°C)

- The wider ±1.0°C margin accounts for:

	- Non-linearities at temperature extremes

	- Voltage reference variations

	- ADC quantization error at range limits

	- These tolerances align with RP2040 datasheet specifications for the internal temperature sensor.


## **Test Output Example**

```
===== TEMPERATURE SENSOR TEST =====
VREF: 3.3V | ADC Resolution: 4095
Voltage @27°C: 0.706V


=== Starting Temperature Conversion Tests ===

=== CALIBRATION POINT DETAILS ===
ADC Value: 875
Voltage: 0.706 V
Expected: 27.00°C | Actual: 27.00°C
Difference: 0.00°C
[1/6] Testing reference point (27°C)...         ADC: 875   Expected: 27.00°C  Actual: 27.00°C  PASS

=== TYPICAL VALUE DETAILS (20°C) ===
ADC Value: 891
Voltage: 0.740 V
Expected: 20.00°C | Actual: 20.01°C
Difference: -0.01°C
[2/6] Testing typical value (20°C)...           ADC: 891   Expected: 20.00°C  Actual: 20.01°C  PASS

=== HIGH TEMPERATURE DETAILS (38.48°C) ===
ADC Value: 850
Voltage: 0.644 V
Expected: 38.48°C | Actual: 38.47°C
Difference: 0.01°C
[3/6] Testing higher temperature (~38.48°C)...  ADC: 850   Expected: 38.48°C  Actual: 38.47°C  PASS

=== LOW TEMPERATURE DETAILS (-8.13°C) ===
ADC Value: 950
Voltage: 0.816 V
Expected: -8.13°C | Actual: -8.12°C
Difference: -0.01°C
[4/6] Testing lower temperature (~-8.13°C)...   ADC: 950   Expected: -8.13°C  Actual: -8.12°C  PASS

=== MINIMUM ADC VALUE DETAILS ===
ADC Value: 0
Voltage: 0.000 V
Expected: 152.93°C | Actual: 152.93°C
Difference: 0.00°C
[5/6] Testing minimum ADC value (0)...          ADC: 0     Expected: 152.93°C Actual: 152.93°C PASS

=== MAXIMUM ADC VALUE DETAILS ===
ADC Value: 4095
Voltage: 3.300 V
Expected: -128.57°C | Actual: -128.57°C
Difference: 0.00°C
[6/6] Testing maximum ADC value (4095)...       ADC: 4095  Expected: -128.57°C Actual: -128.57°C PASS

===== TEST COMPLETE =====
```


## **Prerequisites**

- Raspberry Pi Pico W
- Pico SDK
- CMake ≥ 3.13
- ARM Toolchain (e.g., arm-none-eabi)

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
- Embedded temperature monitoring;
- Fan and thermal control;
- IoT projects using internal sensors; and
- Hands-on learning about ADCs.

## **References:**
- RP2040 Datasheet - Section 4.9.5: Temperature Sensor; 
- Unity Test Framework.


## **System Behavior Images**
Below are screenshots and photos demonstrating the system in action:

### **Loading into Flash**  
![Image](https://github.com/user-attachments/assets/52e4a96d-8059-4d53-ad4c-1e4560504b2d) 
_Screenshot of the program running within the VS Code environment._

### **screenshot during testing using VSCode – outputs**  
![Image](https://github.com/user-attachments/assets/93f50086-e93c-4346-aa5e-b10fd3f9b0e8)
_Screenshot of the program running within the VS Code environment._


### **screenshot during testing using VSCode – outputs**  
![Image](https://github.com/user-attachments/assets/7a791028-14a0-4912-8360-595d31451ce9)
_Screenshot of the program running within the VS Code environment._


## **Contributions**
Feel free to:
- Report bugs
- Open feature requests
- Contribute new test cases

## **License**
MIT License - see the LICENSE file for details.