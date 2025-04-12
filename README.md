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
 | [Project_1: Digital Galton Board](./projects/digital_galton_board/) | Simulation of random events with OLED display visualization and histogram |  
 | [Project_2: Sound Synthesizer](./projects/sound_synthesizer/) | Sound generation using buttons and a buzzer |  
 | [Project_3: Balancing Robot](./projects/balancing_robot/) | A two-wheeled self-balancing robot with PID control |  
 
 ---  
 
 ## **My BitDogLab**  
 
 ![Image](https://github.com/user-attachments/assets/22049b52-f9ec-4e72-bb2c-1a0df1b4a48c)  
 
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
 
 2 - [**Reading Analog Signals from a Joystick**](https://github.com/filipe19/)| ...
 
 3 - [**Monitoring the MCU's Internal Temperature**](https://github.com/filipe19/)| ...
 
 ---
 
 
 ### **Week 7:**  
 
 ---  
 