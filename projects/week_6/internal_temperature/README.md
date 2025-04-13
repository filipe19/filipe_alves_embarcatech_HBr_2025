# ** Internal Temperature [T] Reader – RP2040 + OLED Display**

This project demonstrates how to **read and display the internal temperature** of the RP2040 microcontroller (used in the Raspberry Pi Pico W), using the **BitDogLab** development board. The temperature data is shown both on the **serial monitor** and on a **0.96" I2C OLED display**.

---

## **What This Project Covers**

This implementation shows how to:
- Initialize and configure the **I2C protocol** for an OLED display;
- Use the **internal ADC** (analog-to-digital converter) to read the on-chip temperature sensor;
- Convert the ADC value into degrees Celsius using the **formula from the RP2040 datasheet**;
- Format and display temperature data both on the **terminal** and the **OLED display**.

---

## **Understanding the Internal Temperature Sensor**

The RP2040 has a built-in temperature sensor connected to **ADC channel 4**. It measures the voltage (V<sub>BE</sub>) of a biased bipolar junction transistor.

### **Conversion Formula (from the RP2040 Datasheet)**

```
T [°C] = 27 - (V_read - 0.706) / 0.001721
```

- `V_read`: the voltage measured by the ADC.
- `0.706V`: the typical voltage at 27°C.
- `0.001721 V/°C`: the voltage change per degree Celsius.

> **Note**: The formula provides an approximation. For precision applications, consider calibrating the sensor or using an external voltage reference.

Source: [RP2040 Datasheet – Raspberry Pi](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)

---

## **How the System Works**

![Image](https://github.com/user-attachments/assets/4b556fac-25f1-4e44-8695-7ba5b82651ba)
_Temperature Sensor On Chip_

1. The ADC on the Pico W is initialized and the temperature sensor is activated.
2. The ADC reads raw data from channel 4 (internal sensor).
3. The raw value is converted to voltage and then to temperature using the datasheet formula.
4. The temperature is printed on the serial monitor and displayed on the OLED.

---

## **Project Objective**

Create a program in **C** that:
- Reads the internal temperature of the RP2040 using ADC channel 4.
- Displays the temperature in real-time on:
  - the **serial terminal**, and
  - a **0.96” I2C OLED display**.

---

## **Hardware Requirements**

| **Component**              | **Connection (Raspberry Pi Pico W)**             |
|---------------------------|--------------------------------------------------|
| OLED Display (I2C, SSD1306) | SDA → GPIO14<br>SCL → GPIO15                    |
| BitDogLab Board (RP2040)   | Provides access to the RP2040 internal features |

---

## **How to Run**

1. **Prepare Your Environment**
   - Install the **Raspberry Pi Pico SDK**.
   - Use **Visual Studio Code** with **CMake Tools** and **GCC ARM toolchain**.

2. **Build the Project**
   - Open the folder in VS Code.
   - Use `Ctrl + Shift + B` to build, or run `cmake` and `make` in the terminal.

3. **Upload to Pico**
   - Connect the Pico W to USB while holding the **BOOTSEL** button.
   - Copy the generated `.uf2` file to the **RPI-RP2** USB drive.

4. **Run the Program**
   - Open a serial terminal (e.g., PuTTY, minicom, or VS Code serial monitor).
   - Temperature will be displayed every second on the terminal and OLED.

---

## **File Structure**

| **File**                   | **Description**                                        |
|----------------------------|--------------------------------------------------------|
| `internal_temperature.c`   | Main source code: sensor reading and display output    |
| `CMakeLists.txt`           | Project configuration and library linking              |
| `ssd1306.h/.c`             | OLED display driver library (I2C communication)        |

---

## **System Demonstration**

![Image](https://github.com/user-attachments/assets)
_Code Terminal Output_
 
![Image](https://github.com/user-attachments/assets) 
_BitDogLab + OLED Display_

---

## **License**

This project is licensed under the [MIT License](LICENSE).
