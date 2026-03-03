# Speed ECU – Speed Calculation Node

## Overview

This ECU is responsible for measuring vehicle speed (simulated using a potentiometer) and transmitting the speed value via CAN Bus to the Main Dashboard ECU.

The potentiometer acts as a throttle input for speed simulation.


## Working Principle

1. Potentiometer produces analog voltage.
2. SPI interface reads ADC value from MCP3204.
3. 12-bit digital value is obtained.
4. ADC value is mapped to speed range (0–100 km/h).
5. Speed is transmitted via CAN Bus.


## Output

- Continuously transmits simulated vehicle speed via CAN Bus.
