# **EmbarcaTech HBr 2025**

**Institution:** Instituto Hardware BR-DF
**Course:** Technological Residency in Embedded Systems
**Author:** Filipe Alves de Sousa
**Brasília-DF, May 2025**

# **Digital Galton Board**

## Problem Setup

In an idealized Galton board, like the one shown in Figure 1, a ball bounces off a single pin in each row of the board. When the ball hits a pin, it has a 50% chance of bouncing left and a 50% chance of bouncing right. In this idealization, the outcome of each bounce is completely independent of the previous ones.

![Image](https://github.com/user-attachments/assets/8b778056-55c2-4cd2-a578-e20ec5abdc4d)

*Figure 1. Overview of the Galton Board (Source: [V. Hunter Adams](https://vanhunteradams.com/Pico/Galton/Galton.html#Introduction))*

A set of bins collects the balls as they fall through the bottom row of the board. We can label these bins starting from the left with increasing integers beginning at 0. The number of bins equals one more than the number of rows in the Galton Board.
The ball drops onto the top center pin, at a position that is half the number of rows. For example, in the 5-row Galton Board shown above, the ball starts at position 2.5. Each collision with a pin has a 50% chance to increase the position by 0.5 (right bounce) and a 50% chance to decrease it by 0.5 (left bounce). The bin it eventually lands in represents the sum of *N* such random trials, where *N* is the number of rows.

## What Is a Galton Board?

It's a physical device that demonstrates how small random decisions lead to a **normal (Gaussian) distribution** when repeated many times (like randomly choosing to go left or right after a bounce).

**Why digital?**
I transformed this concept into an interactive simulator, where we can adjust parameters in real time and instantly see the results.

![Image](https://github.com/user-attachments/assets/7b051d18-c318-43bf-a24c-10185dbc472d)
*Photo of the OLED display during testing – development environment.*

---

This project implements a **digital version** of the **Galton Board** using the Raspberry Pi Pico with the **BitDogLab** kit. The simulation lets you **visually observe in real time** the statistical behavior of particles colliding with fixed pins and accumulating in bins, illustrating concepts such as **binomial distribution**, the **Central Limit Theorem**, and the **Law of Large Numbers**.

---

## Components and Architecture

**Hardware Used:**

* Microcontroller: Raspberry Pi Pico (ARM Cortex-M0+), based on the RP2040
* Display: OLED 128x64 (I2C)
* Controls: 2 buttons (GPIO 5, 6)

![Image](https://github.com/user-attachments/assets/f7c703dd-2d34-49cb-bfd7-568ae25165a4)
*Photo of BitDogLab and, in the background, the VSCode development environment.*

**Code Architecture (C):**

1. **Initialization:** Sets up GPIO, I2C, and display
2. **Physics Simulation:** Updates ball positions and collisions
3. **Rendering:** Draws everything pixel-by-pixel on the OLED using the library in the `inc` folder
4. **Controls:** Buttons A and B, adjusting parameters in real time

![Image](https://github.com/user-attachments/assets/cd1889eb-3e9d-4e18-9ea1-6a7d34c865cd)
*Photo of my implementation in the VSCode development environment.*

---

## Practical Operation

### Randomness and Collisions

* Each ball starts at the center of the top track
* On hitting a pin, it randomly bounces left or right
* Bias can be adjusted via Button B (0 = always left, 5 = 50%, 10 = always right)

### Counting and Distribution

* Balls fall into bottom bins, forming a histogram
* Auto-normalization: Graph resizes to fit the display

### Multiple Simultaneous Balls

* Button A controls how many balls are released per cycle (1 to 5)
* Demonstrates the Law of Large Numbers in practice

---

## Why Is This Project Special?

**Theory meets practice:**
It combines probability theory with embedded systems implementation.

**Technical challenge:**
All graphic processing is done pixel-by-pixel on the microcontroller.

**Interactivity:**
Real-time control of simulation parameters.

---

## Materials and Connections

| Component          | BitDogLab Connection      |
| ------------------ | ------------------------- |
| BitDogLab (RP2040) | Raspberry Pi Pico W       |
| OLED Display I2C   | SDA: GPIO14 / SCL: GPIO15 |
| Button A           | GPIO5                     |
| Button B           | GPIO6                     |

---

## Project Structure

```bash
lab01_galton_board-filipe19/
├── inc/
│   ├── ssd1306.h           # Display control library
│   ├── ssd1306_i2c.[ch]    # I2C driver for the display
│   └── galton_config.h     # Configuration and constants
├── src/
│   ├── galton_display.c    # Rendering and initialization
│   └── galton_simulation.c # Simulation logic
├── assets/                 # Images and demo GIFs
├── CMakeLists.txt          # Build configuration
└── README.md               # Documentation
```

---

## Interactive Controls

| Button  | Function        | Values                            |
| ------- | --------------- | --------------------------------- |
| A (GP5) | Balls per cycle | 1–5 (shown as "A\:X")             |
| B (GP6) | Bias adjustment | 0–10 (0=left, 5=center, 10=right) |

**Display shows:**

* Total balls: "T\:XXXX"
* Normalized histogram
* Visual elements: pins, trajectories, track, bins

---

## Mathematical Principles

```c
// Example: Biased decision
bool random_decision_with_bias() {
    int threshold = map(BALANCE_BIAS, 0, 10, 5, 95);
    return (rand() % 100) < threshold;
}
```

**Concepts demonstrated:**

* Binomial Distribution
* Central Limit Theorem
* Law of Large Numbers
* Stochastic Processes

---

## Adjustable Parameters

| Parameter              | Values  | Effect                |
| ---------------------- | ------- | --------------------- |
| GRAVITY                | 0.1–0.5 | Falling speed         |
| BOUNCINESS             | 0.1–0.9 | Collision elasticity  |
| PIN\_SPACING           | 5–15    | Distance between pins |
| MAX\_HISTOGRAM\_HEIGHT | 10–20   | Max histogram height  |

---

## Video Demo

[![Watch the video](https://img.youtube.com/vi/KARrL2JzPGs/0.jpg)](https://www.youtube.com/watch?v=KARrL2JzPGs)

---

## 🔧 How to Compile

```bash
mkdir build && cd build
cmake ..
make
```

Then upload the `.uf2` file to the Pico.

---

## *Interactive Control:*

Button A (GP5):
Cycles through 1–5 balls released simultaneously
Shown as "A\:X" in the top-left corner

Button B (GP6):
Adjusts bias (0–10)
0 = max bias to left
5 = balanced (default)
10 = max bias to right
Shown as "B\:X" in the top-right corner

## Data Display:

*Total balls:* "T\:XXXX" in the bottom-left corner

*Histogram:*
Automatically normalized
Max height configurable (MAX\_HISTOGRAM\_HEIGHT)

*Visual elements:*
Hexagonal pins
Ball trajectories
Tracks / bins

---

### 1. Total Ball Counter

Below, the counter in the screen corner increases as new balls are generated and fall into bins:

![Total Ball Counter](https://github.com/user-attachments/assets/89c5a211-af18-403d-8df4-4433f3f387c8)

*Photo of my implementation – Total Ball Counter.*

---

### 2. Simulation with Bias

Here, the button was used to apply a right bias. Note the final distribution asymmetry:

![Biased Simulation](https://github.com/user-attachments/assets/5a47eb1e-7c77-463e-b45d-708d8b0dd126)

*Photo of my implementation – Biased Simulation – left/right trend.*

---

### 3. Multiple Balls Simultaneously

In this simulation, several particles fall at once, speeding up histogram formation:

![Multiple Balls at Once](https://github.com/user-attachments/assets/c9208a5b-c449-4274-82e7-0fdb2ce7744b)

*Photo of my implementation – Multiple Balls at Once.*

---

## Requirements

* Raspberry Pi Pico with BitDogLab or similar
* OLED Display SSD1306 (via I2C)
* Buttons
* C/C++ Development Environment with Pico SDK

---

## References

1. Adams, V. H. "Digital Galton Board". Available at: [https://vanhunteradams.com/Pico/Galton/Galton.html](https://vanhunteradams.com/Pico/Galton/Galton.html)
2. Raspberry Pi Pico C/C++ SDK Documentation
3. "The Galton Board: 150 Years of Normal Distribution" – Statistical Science
4. Physical Simulation Principles – David H. Eberly

---

## License

This project is licensed under the [MIT License](LICENSE).

---
