# Ultrasonic ECU – Distance Measurement Node

## Overview

This ECU is responsible for measuring the obstacle distance using an ultrasonic sensor and transmitting the distance data over CAN Bus to the Main Dashboard ECU.

It simulates the front obstacle detection system used in automotive safety applications.

## Working Principle

1. Trigger pulse (10 µs) is generated.
2. Echo pulse width is measured using Timer.
3. Distance is calculated using:

Distance = (Echo Time × Speed of Sound) / 2

4. Distance value is packed into a CAN frame.
5. CAN frame is transmitted to Main ECU.


## CAN Configuration

- CAN Bit Rate: 125 Kbps
- CAN ID: 0x01 (Distance Frame)
- Data Length: 1 byte (Distance)


## Output

- Continuously transmits real-time obstacle distance via CAN Bus.
