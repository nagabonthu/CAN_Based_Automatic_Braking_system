# CAN-Based Automatic Collision Risk Detection & Braking System

## Overview

This project implements a multi-node automotive safety system using CAN Bus communication.  
The system simulates a real-time vehicle environment where speed and obstacle distance are continuously monitored, and automatic braking is applied when collision risk is detected.

The architecture follows a distributed ECU model similar to real automotive systems.  
Each node performs a dedicated function and communicates over CAN Bus.

This project provides Practical experience in:

- Automotive Embedded Systems
- CAN Networking
- Distributed Control Systems
- Real-Time Risk Assessment
- Peripheral Integration
- Safety-Critical Logic Implementation

## System Architecture

The system consists of three independent ECUs connected through CAN Bus.

### 1️⃣ Ultrasonic ECU (Distance Node)

- Uses HC-SR04 Ultrasonic Sensor
- Generates trigger pulse
- Measures echo pulse width using Timer
- Calculates obstacle distance
- Transmits distance data via CAN Bus

This node continuously monitors the obstacle distance in front of the vehicle.

### 2️⃣ Speed ECU (Speed Node)

- Uses MCP3204 12-bit SPI ADC
- Reads analog voltage from potentiometer
- Converts analog signal to digital value
- Maps ADC value to vehicle speed
- Transmits speed data via CAN Bus

The potentiometer is used to simulate vehicle speed in this project.

### 3️⃣ Main Dashboard ECU

- Receives speed and distance frames via CAN
- Displays real-time values on:
  - 16x2 LCD
  - UART terminal
- Calculates Time-To-Collision (TTC)
- Determines collision risk zone
- Controls:
  - Safe zone indicator LED
  - Danger zone indicator LED
  - Relay-based automatic braking

This ECU acts as the central decision-making unit.

### System Actions

- Safe Zone:
  - Vehicle runs normally
  - Safe indicator ON

- Warning Zone:
  - Warning LED activated
  - Driver alert condition

- Danger Zone:
  - Relay activated
  - DC motor/generator stopped
  - Automatic braking applied

When the obstacle is removed, the vehicle resumes normal operation.

## Software

- Embedded C (Bare-Metal Programming)
- Keil µVision IDE
- Flash Magic (for programming LPC2148)
- UART Serial Terminal (for debugging)

## Hardware

- LPC2129 ARM7 Microcontroller
- CAN Transceiver Module
- HC-SR04 Ultrasonic Sensor
- MCP3204 SPI ADC (12-bit)
- Potentiometer (Speed Simulation)
- 16x2 LCD Display
- Relay Module (Brake Control)
- DC Motor / Generator (Vehicle Simulation)

## Working Principle

1. Ultrasonic ECU measures obstacle distance.
2. Speed ECU measures vehicle speed.
3. Both ECUs transmit data via CAN Bus.
4. Main ECU receives speed and distance.
5. TTC is calculated.
6. Collision risk zone is determined.
7. Brake is applied automatically if required.
8. Dashboard continuously updates speed and distance.


