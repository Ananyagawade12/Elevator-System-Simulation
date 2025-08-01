# Simulated Elevator System using Arduino (Tinkercad)

This project simulates a basic 5-floor elevator control system using Arduino, designed and tested on [Tinkercad Circuits](https://www.tinkercad.com/). It uses LEDs to represent floors, buttons for user input, a 7-segment display for the current floor, and direction LEDs to indicate elevator movement.

## Features

- Handles user requests to move between 5 floors.
- Simulates elevator motion with a queue of requests.
- LEDs indicate the active floor and movement direction (up/down).
- 7-segment display shows the current floor.
- Uses basic Arduino C programming without external libraries.

## Components (Simulated)

- Arduino Uno (simulated in Tinkercad)
- 5 LEDs for floors (A0–A4)
- 1 Up LED
- 1 Down LED
- 5 Push buttons for floor requests
- 7-segment display

## Core Concepts Used

- Digital input and output
- Debounce-safe input polling using `INPUT_PULLUP`
- Queue logic for request handling
- 7-segment display bit mapping
- Simulation of time delay for floor movement

## 📷 Tinkercad Circuit (Optional)

If you want to try it yourself, recreate the circuit on Tinkercad using the above components and upload the `.ino` file into the Code Editor.

---
