# **EmbarcaTech HBr 2025**  

 Institution: Instituto Hardware BR-DF  
 Course: **Technological Residency in Embedded Systems**  
 Author: **Filipe Alves de Sousa**  
 Brasília-DF, March 2025  
 
 ## **About This Repository**  
 This repository contains the projects developed throughout the Embedded Systems course during the technological residency phase. Each project has its own folder, containing source code, documentation, and visual resources.  
 
 ---  
 
 ## **Project List**  
 
 | Project | Description |  
 |---------|------------|  
 | [Project_1: Digital Galton Board](https://github.com/filipe19/filipe_alves_embarcatech_HBr_2025/tree/main/projects/week_8/lab01_galton_board-filipe19) | Simulation of random events with OLED display visualization and histogram |  
 | [Project_2: Sound Synthesizer](./projects/sound_synthesizer/) | Sound generation using buttons and a buzzer |  
 | [Project_3: Balancing Robot](./projects/balancing_robot/) | A two-wheeled self-balancing robot with PID control |  
 
 ---  
 
 ## **My BitDogLab**  
 
 ![Image](https://github.com/user-attachments/assets/714fca2b-53e3-47e3-8410-cef01dea8342)  
 
 _Photo of the BitDogLab board._  
 
 ---  
 
 ## **Logbook [Reflections and Learnings]**  
 
 Throughout the course, this section will be updated with key learnings, challenges faced, and solutions found. This practice helps document the development journey and facilitates future review.  
 
 ### **Week 1 - 4:**  
 - I presented my final project from the first phase, which consisted of a [Adaptive Lighting System with RGB LEDs for Studying the Behavior of Children with ADHD](https://github.com/filipe19/Embarcatech-BitDogLab-RaspberryPi). Receiving feedback from colleagues was an enriching experience. I realized that each person brought unique ideas and different approaches to overcoming the challenges of the final project.  
 
 ---
 
 ### **Week 5:**  
 - We took a trip to **FINATEC** and the **Faculty of Technology (FT)** at the University of Brasília (UnB), where we had the opportunity to explore several research laboratories and learn about a wide range of innovative projects. Among them were the [Empowering Mobility and Autonomy (EMA) Project](https://www.ene.unb.br/antonio/ema/pt/index.html), the [UnBeatables robotics team](https://noticias.unb.br/publicacoes/112-extensao-e-comunidade/90-equipe-de-robotica-da-unb-e-bicampea-de-competicao-internacional) at the LARA Lab, the [CubeSat Nanosatellite Project](https://noticias.unb.br/117-pesquisa/5614-nanossatelite-desenvolvido-na-unb-esta-em-orbita), the [Apuama Racing competitive car systems](http://ft.unb.br/index.php?option=com_content&view=article&id=13&Itemid=123), 3D printing initiatives, an image processing project, and the [Advanced Nanostructured Materials Laboratory (LaMNA)](http://www.ppgcima.unb.br/organizacao/infra-lab), among others.
 
 Visiting these labs was a truly inspiring experience. Seeing real-world applications of engineering and technology — many of which were developed by undergraduate and graduate students — showed us how knowledge, collaboration, and innovation come together to build impactful solutions. It reinforced the importance of hands-on experience and creativity in shaping future technologies and made me even more motivated to be part of this growing and transformative field.
 
 ---
 
 ### **Week 6:**  
 - In addition to studying **Microcontroller Architectures and Manufacturers**, we also worked on practical implementations, such as:
 
 1 - [**Countdown Timer with Event Logging via Interrupts**](https://github.com/filipe19/filipe_alves_embarcatech_HBr_2025/tree/main/projects/week_6/decrementing_count) | This implementation included a **software-based debounce solution for button input**. The debounce was handled using a waiting period (`delay`) based on the `absolute_time_diff_us` function to ensure that a minimum interval (defined as 300 ms via `DEBOUNCE_TIME_MS`) had passed since the last button press.  
 This approach prevented multiple rapid presses caused by mechanical or electrical noise from being incorrectly registered as valid clicks during the countdown interval.
 
 2 - [**Reading Analog Signals from a Joystick**](https://github.com/filipe19/filipe_alves_embarcatech_HBr_2025/tree/main/projects/week_6/Joystick_test)| This project implements a **joystick reader**, utilizing the Raspberry Pi Pico and the BitDogLab board to read joystick inputs and monitor system behavior. The main goal is to demonstrate the use of analog-to-digital conversion (ADC) for joystick inputs and display real-time data both on the serial monitor and on an OLED display.
 
 3 - [**Monitoring the MCU's Internal Temperature**](https://github.com/filipe19/filipe_alves_embarcatech_HBr_2025/tree/main/projects/week_6/internal_temperature)| This hands-on implementation demonstrated how to initialize and configure I2C and the OLED display; how to use the internal ADC to read the RP2040's chip temperature; how to convert the ADC value into temperature using the formula from the datasheet; and how to display formatted messages both on the terminal and the display.
 
 ---
 
 
 ### **Week 7:**  

This week, the AgroHealth – Intelligent Monitoring System for Medicinal Plants project proposal was developed in a group, applying the concepts of the 6-layer IoT model:
Perception: sensors (moisture, pH, imaging, etc.); Network: connectivity (LoRaWAN); Edge: ESP32/Jetson; Cloud Storage; Abstraction via API; and Application: presentation through dashboards.
The system enables remote monitoring of plantations, with alerts, automatic irrigation control, and OTA (Over-The-Air) updates, allowing reprogramming of Pico W and ESP32 devices without physical access.

Projects 1 and 2 were also implemented: the modular restructuring of a blinking LED using a HAL/driver/app architecture, and conversion of internal temperature sensor readings via ADC to Celsius, including unit testing with Unity.

 1 - [**Modular LED Blinker for Raspberry Pi Pico W**](https://github.com/filipe19/filipe_alves_embarcatech_HBr_2025/tree/main/projects/week_7/struct_blink) | We implemented a modular architecture for controlling the built-in LED on the Raspberry Pi Pico W, organized into three layers: Driver (direct hardware access), HAL (hardware abstraction), and Application (main logic). This structure ensures good organization, facilitates testing, maintenance, and code reuse, while also demonstrating solid design practices for embedded systems. The project highlights benefits such as portability, structural clarity, and practical learning in hardware interaction.

 2 - [**Internal Temperature Reader with ADC for Raspberry Pi Pico W**](https://github.com/filipe19/filipe_alves_embarcatech_HBr_2025/tree/main/projects/week_7/unity_test_adc_temperature) | This project presents an efficient implementation of the RP2040 microcontroller’s internal temperature sensor, using the manufacturer's official conversion equation to obtain accurate readings in degrees Celsius from the ADC. The code was developed with a focus on clarity, optimization, and documentation, as well as including unit tests to validate results under different thermal conditions. Its application is ideal for embedded systems and IoT devices that require basic thermal monitoring, eliminating the need for external sensors and serving as an educational foundation for studies on ADCs and integrated sensors.

 ---  
 
 ### **Week 8:**  

This week, the Digital Galton Board project was developed using the BitDogLab platform with the Raspberry Pi Pico. The application simulated the behavior of a digital Galton Board, allowing the visualization of the statistical distribution resulting from multiple particles (balls) colliding with obstacles and accumulating in lower compartments (receptacles).

The system explored concepts such as the binomial distribution, normal (Gaussian) distribution, the Central Limit Theorem, and the Law of Large Numbers, while also applying principles of collision physics with control over parameters such as gravity, restitution coefficient, and velocity. User interaction was implemented through digital buttons (interrupts), and real-time visualization was displayed on an SSD1306 OLED screen via I2C. In future iterations, the project may also include a buzzer for collision sound effects, controlled via PWM and DMA.

The code was structured in layers and split into multiple files to facilitate maintenance, testing, and scalability.

1 - [**Digital Galton Board with Raspberry Pi Pico W and BitDogLab**](https://github.com/filipe19/filipe_alves_embarcatech_HBr_2025/tree/main/projects/lab01_galton_board-filipe19) | The project digitally simulated a Galton Board with multiple simultaneous particles, physical parameter control via buttons, graphical OLED display, and real-time statistics. A modular structure was adopted with separation between the application layer, simulation logic, input control, and graphical interface. This implementation enhanced the understanding of statistical phenomena while strengthening skills in embedded programming, analog input reading, peripheral usage, and clean code organization.