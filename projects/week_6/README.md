# **EmbarcaTech HBr 2025 - Week 6**  

Institution: Instituto Hardware BR-DF  
Course: **Technological Residency in Embedded Systems**  
Author: **Filipe Alves de Sousa**  
Brasília-DF, April 2025  

## **About This Repository**  
- In addition to studying **Microcontroller Architectures and Manufacturers**, we also worked on practical implementations, such as:

## **Project List**  

| Project | Description |  
|---------|------------|  
| [Project_1: **Countdown Timer with Event Logging via Interrupts**](https://github.com/filipe19/filipe_alves_embarcatech_HBr_2025/tree/main/projects/week_6/decrementing_count) | This implementation included a **software-based debounce solution for button input**. The debounce was handled using a waiting period (`delay`) based on the `absolute_time_diff_us` function to ensure that a minimum interval (defined as 300 ms via `DEBOUNCE_TIME_MS`) had passed since the last button press. This approach prevented multiple rapid presses caused by mechanical or electrical noise from being incorrectly registered as valid clicks during the countdown interval.|  
| [Project_2: **Reading Analog Signals from a Joystick**](https://github.com/filipe19/filipe_alves_embarcatech_HBr_2025/tree/main/projects/week_6/Joystick_test) | This project implements a **joystick reader**, utilizing the Raspberry Pi Pico and the BitDogLab board to read joystick inputs and monitor system behavior. The main goal is to demonstrate the use of analog-to-digital conversion (ADC) for joystick inputs and display real-time data both on the serial monitor and on an OLED display.|  
| [Project_3:**Monitoring the MCU's Internal Temperature**](https://github.com/filipe19/filipe_alves_embarcatech_HBr_2025/tree/main/projects/week_6/internal_temperature) | This hands-on implementation demonstrated how to initialize and configure I2C and the OLED display; how to use the internal ADC to read the RP2040's chip temperature; how to convert the ADC value into temperature using the formula from the datasheet; and how to display formatted messages both on the terminal and the display.|  

---  

## **License**  

This project is licensed under the [MIT License](LICENSE).