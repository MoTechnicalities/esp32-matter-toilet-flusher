# ESP32 Matter Toilet Flusher

Tired of manually flushing your toilet? Take control with smart home automation!  

This open-source project will help you build a DIY toilet flusher using an ESP32 microcontroller and a servo. Enjoy the convenience and accessibility of automated flushing with your favorite smart home platforms, like Apple Home, Alexa, and Google. It's a great way to add a touch of tech to your bathroom and potentially save water too!  

![image](https://github.com/MoTechnicalities/esp32-matter-toilet-flusher/assets/68468472/0c25c598-983b-45c8-b5d7-26047e2a724a)
![image](https://github.com/MoTechnicalities/esp32-matter-toilet-flusher/assets/68468472/8f62bbc7-c20e-4726-8e97-d4e22ab0b084)

  <b>Notice:</b> Affeliate links may be provided for the products used to create this project. Please consider using them when available if you decide to purchase the items. Using the links will help me to continue providing helpful content at no caust to you.  
## Table of Contents

[Features](https://github.com/MoTechnicalities/esp32-matter-toilet-flusher/tree/main#table-of-contents)  
[Hardware Requirements](https://github.com/MoTechnicalities/esp32-matter-toilet-flusher/tree/main#hardware-requirements)  
[Software Requirements](https://github.com/MoTechnicalities/esp32-matter-toilet-flusher/tree/main#software-requirements)  
[Installation](https://github.com/MoTechnicalities/esp32-matter-toilet-flusher/tree/main#installation)  
[Usage](https://github.com/MoTechnicalities/esp32-matter-toilet-flusher/tree/main#usage)  
[Contributing](https://github.com/MoTechnicalities/esp32-matter-toilet-flusher/tree/main#contributing)  
[License](https://github.com/MoTechnicalities/esp32-matter-toilet-flusher/tree/main#license)  
[Contact](https://github.com/MoTechnicalities/esp32-matter-toilet-flusher/tree/main#contact)

## Features

<b>Matter protocol support:</b> Compatible with various smart home ecosystems for seamless integration.  
<b>Automated flushing:</b> Combine with motion or occupancy sensors to auto flush or schedule specific flush times.  
<b>Remote control:</b> Trigger flushes from your smartphone or voice assistant.  
<b>Potential water savings:</b> Conserve water by flushing only when needed.  
<b>Accessible design:</b> Can be adapted for individuals with limited mobility and offers optional ability to add hand or foot operated momentary contact button(s) and an optional LED indicator.  

## Hardware Requirements

<b>ESP32 microcontroller:</b>  
![image](https://github.com/MoTechnicalities/esp32-matter-toilet-flusher/assets/68468472/95daf1dc-c422-453a-a972-34da97d16c24)    
    This project was developed using an [ESP32 WROOM-32](), but any ESP32 microcontroller with Wi-Fi connectivity and enough memory to run the code is compatible. Popular options include ESP32-D0WD-Q6, ESP32-S2, and ESP32-CAM.

However, for users interested in Matter over Thread functionality, newer models like the ESP32-H2 specifically support this protocol and may offer additional benefits. Remember to check your chosen model's memory requirements and Thread/Matter compatibility before proceeding.

<b>Servo motor:</b>  
![image](https://github.com/MoTechnicalities/esp32-matter-toilet-flusher/assets/68468472/0e4d99b0-0b74-405d-b336-5b5b734b5b82)    
    You will want a servo motor with sufficient torque to reliably flush your toilet's water tank. A minimum torque rating of 2kg-cm is recommended, but adjust this based on your specific tank's requirements. The servo should also be compatible with the ESP32's 5V power output. Popular options include the budget-friendly SG90 9G Servo or the MG90 9G Servo with metal gears for increased durability and handling higher torque demands. If your setup requires using a higher-torque servo, multiple servos, or desiring added reliability, consider using a separate power supply to avoid overloading the ESP32. Remember to verify your chosen servo's torque rating and power requirements before proceeding.  
    
<b>Power supply:</b>  
![image](https://github.com/MoTechnicalities/esp32-matter-toilet-flusher/assets/68468472/fe6838d3-5d2d-44de-b2ce-559d408305a5)  
    The ESP32 WROOM-32 has a standard Micro USB connector and requires a 5-volt DC power supply. For most setups, a power supply with 2.5 Amps should be sufficient. However, always match the power supply's connector type (e.g., Micro USB) to your specific ESP32 model. Consider these recommendations for different scenarios:  
  --<b>High-torque servo or multiple servos:</b> Adjust your power supply choice based on their combined current requirements. You might need a higher amperage rating (e.g., 3A or 5A) to avoid overloading.  
  --<b>Portability or testing:</b> A power bank with sufficient capacity and 2.5 Amp output can be convenient.  
  --<b>Off-grid use:</b> Choose a 5V lithium-ion battery pack with adequate capacity and built-in safety features.
    
<b>Breadboard and jumper wires</b>  
    The first breadboards I used to develop this project was the BOJACK 3 Values 130 Pcs Solderless Breadboard 4 Pcs 830 Tie Points & 400 Tie Points & 126 Pcs Flexible Breadboard Jumper Wires.   
    ![image](https://github.com/MoTechnicalities/esp32-matter-toilet-flusher/assets/68468472/345cd2ff-cdad-4c25-ac5b-f8bee517f102)    
      The second for my final assembly was the ESP32 Breakout Board GPIO 1 into 2 Compatible with 30 Pins ESP32S ESP32 Development Board 2.4 GHz Dual Core WLAN WiFi + Bluetooth 2-in-1 Microcontroller ESP-WROOM-32 Chip for Arduino  
    ![image](https://github.com/MoTechnicalities/esp32-matter-toilet-flusher/assets/68468472/6f721764-9ccf-4797-89d6-da9c91be9088)

<b>Toilet tank drain stop assembly (for installation)</b>  
Your toilet tank may differ, however, the idea is to set up the servo so that as it rotates from 0 to 180 degrees for about 2 seconds it will momentarily lift the toilet tank's drain stop or flap to allow for the flush in the same way as the manual lever does. In my case, I was conveniently able to set up my toilet tank's drain stop assembly as shown in the picture. A small amount of super-glue was more than sufficient to secure the servo. Copper wire was used to form a handmade chain to link the servo to the drain stop. My toilet tank's drain stop assembly is out of a newer Glacier Bay toilet with Power Flush. Your toilet may have a completely different design and adjustments in your arrangement will likely be required as there are innumerable types.  

![image](https://github.com/MoTechnicalities/esp32-matter-toilet-flusher/assets/68468472/b32c0ceb-3d1e-4dbc-9796-ec690edba42c)


## Software Requirements

<b>Arduino IDE:</b> There are a number of development platforms available to program the ESP32. For this project there is no need for overkill and the Arduino IDE is all that is needed. To properly set up the Arduino IDE for Matter, C++ code compiling must be Enabled. Follow the steps provided in the [esp32-arduino-matter](https://github.com/Yacubane/esp32-arduino-matter#installing-on-arduino-ide) repository. After following the setup procedure, return here.  

<b>ESP32Servo:</b> Install the <b>ESP32Servo</b> library by Kevin Harrington. This [YouTube Video](https://www.youtube.com/watch?v=e7D_n1LeyKk) shows you how.  

## Installation

    Clone this repository to your local machine.
    Open the project in the Arduino IDE.
    Install the required libraries.
    Connect your ESP32 and servo to your computer.
    Upload the code to your ESP32.

## Usage

    Follow the instructions in the code to configure your Wi-Fi and Matter settings (if applicable).
    Install the servo mechanism on your toilet tank.
    Use your smart home app or voice assistant to control the flusher.

## Contributing

We welcome contributions to this project! Please feel free to:

    Submit bug reports or feature requests.
    Create pull requests to improve the code or documentation.
    Share your own experiences and modifications.

## License

This project is licensed under the Apache License, Version 2.0: LICENSE: LICENSE.

## Contact

For any questions or feedback, please reach out to Your Name or GitHub Username: Link to your GitHub Profile: Link to your GitHub Profile.
