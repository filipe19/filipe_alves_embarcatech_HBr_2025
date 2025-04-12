# **Interrupt-Driven Countdown with Event Logging**

This project implements a **countdown timer controlled by interrupts**, using button presses to trigger and monitor system behavior. The main goal is to demonstrate the use of interrupts to handle user inputs during an active process and display real-time data using an OLED display.

---

## **Objective**

Create a program in C that:

- Starts a countdown from 9 to 0 when **Button A (GPIO5)** is pressed.
- During the countdown, counts how many times **Button B (GPIO6)** is pressed.
- Displays both the countdown and the event count on the **OLED display**.
- Freezes the system once it reaches 0, only restarting when **Button A** is pressed again.

---

## **Materials List**

| Component            | Connection on BitDogLab     |
|----------------------|-----------------------------|
| BitDogLab (RP2040)   | Raspberry Pi Pico W         |
| OLED Display I2C     | SDA: GPIO14 / SCL: GPIO15   |
| Button A             | GPIO5                       |
| Button B             | GPIO6                       |

---

## **Execution**

1. Open the project in **VS Code** using an environment set up for the Raspberry Pi Pico SDK (CMake + ARM GCC).
2. Build the project with **Ctrl+Shift+B** or via terminal using `cmake` and `make`.
3. Connect the BitDogLab via USB and boot the board into bootloader mode (press and hold BOOTSEL while plugging in).
4. Copy the generated `.uf2` file to the **RPI-RP2** drive.
5. The program will begin running automatically:
   - OLED shows `9` when Button A is pressed.
   - Countdown begins and decrements every second.
   - Every press of Button B during the countdown is recorded and displayed.
   - At `0`, the system freezes and displays final count.
   - Only another press on Button A resets and restarts the process.

---

## **Logic**

- **Button A (GPIO5)** triggers an interrupt that:
  - Resets countdown to 9
  - Starts a 1-second timer-based decrement loop
  - Resets Button B counter
- **Button B (GPIO6)** triggers an interrupt that:
  - Increments a counter only during active countdown
- Countdown and event count are shown in real-time on the **OLED**.
- Once countdown reaches **0**, system locks and ignores Button B until restarted with Button A.

---

## **Files**

- `decrementing_count.c`: Main logic and interrupt handling.
- `CMakeLists.txt`: Build configuration.

---

## **System Behavior Images**

## **My BitDogLab**  

![Image](https://github.com/user-attachments/assets/3659681c-c750-4271-abe4-fc12b04a36d2)  

_Photo of the BitDogLab board._  

![Image](https://github.com/user-attachments/assets/2880ef58-302c-4b63-9c10-7fb33206e5c2)  

_Photo of my implementation in the VSCode developmente environment._  

---  

---

## **License**

This project is licensed under the [MIT License](LICENSE).
