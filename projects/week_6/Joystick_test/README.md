# **Joystick Reader**

This project implements a **joystick reader**, utilizing the Raspberry Pi Pico and the BitDogLab board to read joystick inputs and monitor system behavior. The main goal is to demonstrate the use of analog-to-digital conversion (ADC) for joystick inputs and display real-time data both on the serial monitor and on an OLED display.

---

## **What is a Joystick?**

A joystick is an input device commonly used for control in various applications. It typically consists of:
- **Two potentiometers**: Responsible for measuring movement along the Y (horizontal) and X (vertical) axes.
- **Digital button**: Used to register additional input, like a "click" or "press."
- **Voltage range**: Operates within 0 to 3.3 volts.
- **Analog-to-Digital Conversion (ADC)**: Maps the continuous analog input values (voltage levels) into discrete digital values. The RP2040 microcontroller (used in Raspberry Pi Pico) has a 12-bit ADC resolution, meaning it can represent inputs in the range of **0 to 4095** (2<sup>12</sup> = 4096 discrete levels).

The joystick reader captures values for both axes (X and Y) and processes them with a scaling factor of **(3.3V / 4096) = ~0.0008056640625** per ADC step.

---

## **Logic**

---
![Image](https://github.com/user-attachments/assets/65424078-39ab-43de-83d7-bf77bba2b128)
_Illustration of how a joystick works_


- **Joystick Movement**:

  - **Y-axis**:
    - Left: **~2047 to ~0**
    - Right: **~2048 to ~4095**

  - **X-axis**:
    - Up: **~2047 to ~0**
    - Down: **~2048 to ~4095**

- **Button State (Z-axis)**:
  - **0**: Not pressed = OFF.
  - **1**: Pressed = ON.

- The OLED Display will mirror the data shown in the serial monitor.

---

---

## **Objective**

Create a program in C that:
- Reads and processes joystick axis values (X and Y) and the state of the button.
- Displays real-time joystick data on both the serial monitor and an OLED display.

---

## **Materials List**

| **Component**          | **BitDogLab (RP2040): Connection on Raspberry Pi Pico W**            |
|-------------------------|----------------------------------------------------------------------|
| OLED Display (I2C)      | **SDA:** GPIO14 / **SCL:** GPIO15                                   |
| Joystick                | **SW:** GPIO22, **ADC0:** GPIO26 (vRx), **ADC1:** GPIO27 (vRy), VCC: 3.3V |

---

## **Execution**

1. **Prepare the environment**:
   - Install the Raspberry Pi Pico SDK in VS Code (with CMake and ARM GCC).
2. **Build the Project**:
   - Use **Ctrl+Shift+B** or the terminal commands `cmake` and `make` to compile the code.
3. **Upload the Program**:
   - Connect the Raspberry Pi Pico (BitDogLab) via USB.
   - Enter bootloader mode by holding **BOOTSEL** while plugging in the board.
   - Copy the generated `.uf2` file to the **RPI-RP2** drive.
4. **Run the Program**:
   - The joystick values (X, Y, and button state) will now be displayed both in the serial monitor and on the OLED.


## **Files**

- **`joystick_test.c`**: Contains the main program logic for reading joystick data and displaying it.
- **`CMakeLists.txt`**: Configures the build process, including linking the necessary libraries.

---

## **System Behavior Images**

Below are screenshots and photos demonstrating the system in action:

![Image](https://github.com/user-attachments/assets/8728358f-b4a7-49de-a03e-948fff1a381b)  
_Photo of the BitDogLab board connected to the OLED display and joystick._

![Image](https://github.com/user-attachments/assets/3c67c388-c811-408d-98ed-371a6b99fe32)  
_Screenshot of the program running within the VS Code environment._

---

## **License**

This project is licensed under the [MIT License](LICENSE).

