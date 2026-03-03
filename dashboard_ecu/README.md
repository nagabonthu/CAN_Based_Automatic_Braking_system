# Main Dashboard ECU – Collision Risk & Braking Control Unit

## Overview

This ECU acts as the central decision-making unit of the system.

It receives distance and speed data from other ECUs via CAN Bus, calculates collision risk, displays information, and controls automatic braking.


## Hardware

- LPC2148 ARM7 Microcontroller
- CAN Transceiver Module
- 16x2 LCD Display
- UART Serial Interface
- Relay Module (Brake Control)
- LED Indicators (Safe/Danger Zones)
- Power Supply & Passive Components

## Working Principle

1. Receives Distance Frame from Ultrasonic ECU.
2. Receives Speed Frame from Speed ECU.
3. Displays real-time values on LCD and UART.
4. Calculates Time-To-Collision (TTC):

TTC = Distance / Speed

5. Determines collision risk zone:
   - Safe Zone
   - Warning Zone
   - Danger Zone

6. If Danger Zone:
   - Relay activated
   - DC motor/generator stopped
   - Brake applied automatically

7. If Safe:
   - Vehicle runs normally


## Output

- Displays speed and distance
- Indicates collision risk level
- Automatically controls braking mechanism
