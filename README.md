# Self-Parking Car Project

## Project Overview
This project aims to design a system for a self-parking car using a miniature 2WD chassis to simulate a real car’s parking mechanisms. The system uses various sensors to detect parking spaces and navigate the vehicle into the space automatically.

The project is built around the ATMEGA32A microcontroller and integrates several hardware components such as DC motors, IR obstacle sensors, ultrasonic sensors, and a 16x2 LCD for displaying the car's status.

![Project Overview](./path-to-your-image) <!-- Add image path here -->

## Features
- **Microcontroller**: ATMEGA32A
- **Sensors**: 2 IR sensors and 1 Ultrasonic sensor
- **Display**: 16x2 LCD for status updates
- **Power**: 9V power supply
- **Finite State Machine (FSM)** to control the car's actions
- **Motors**: Dual motor setup controlled via the L298N motor driver

## Hardware Components
1. **2WD Vehicle Chassis**: The basic frame of the vehicle used to hold other components.
2. **L298N Motor Driver**: Controls the speed and direction of the DC motors.
3. **IR Obstacle Sensors**: Detect obstacles around the vehicle.
4. **Ultrasonic Sensor**: Measures distances to detect the size of parking spaces.
5. **16x2 LCD Display**: Shows parking status and sensor readings.
6. **ATMEGA32A Microcontroller**: Manages sensor inputs and motor control.
7. **DC Motors**: Used to drive the vehicle forward, backward, and for steering.
8. **Breadboard and Wires**: For circuit assembly.

![Hardware Components](./path-to-your-image) <!-- Add image path here -->

## Software Components
The project is developed using **Atmel Studio**, employing a **finite state machine (FSM)** to manage different parking stages:
- **IDLE**: The car remains stationary.
- **FIND_SPACE**: The car moves forward, looking for a suitable parking space.
- **ANGLE**: Adjusts the car’s angle to align with the parking spot.
- **PARKING**: The car maneuvers into the parking space using feedback from sensors.
- **PARKED**: The car is parked, and the process is complete.

The code is written in **C** and is divided into different modules for sensor readings, motor control, and LCD display.

![FSM Diagram](./path-to-your-image) <!-- Add image path here -->

## Results
The project successfully demonstrated the concept of a self-parking car using a microcontroller. Although the system worked as intended in the early stages, some limitations arose due to power supply issues and unreliable motors over time.

## Challenges and Improvements
1. **Chassis Issues**: The structure of the chassis was not robust enough for long-term performance.
2. **Power Supply**: The motors became unresponsive after some time, indicating insufficient or inconsistent power.
3. **Sensor Accuracy**: The sensors worked well initially, but further calibration could improve long-term accuracy.

## Conclusion
This project showcased a simplified version of a real-world self-parking system using accessible hardware and software tools. Future iterations could focus on improving the power system and enhancing motor reliability.

## Usage Instructions
1. Clone the repository.
2. Use **Atmel Studio** to compile and upload the code to the ATMEGA32A microcontroller.
3. Connect the hardware components as per the schematic.
4. Power the system, and the vehicle will start searching for a parking space automatically.

## Contributors
- Muhammad Danish Khattak
- Tahir Nadeem

