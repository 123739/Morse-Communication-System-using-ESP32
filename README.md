# Morse-Communication-System-using-ESP32

## Overview

This project is an embedded communication system that converts user-input text into Morse code and outputs it through multiple channels: visual (LED), auditory (buzzer), and textual (LCD display).

It demonstrates how a single input signal can be encoded and expressed across different forms, making it a simple but effective model of low-bandwidth communication systems.

---

## Features

* Real-time text to Morse code conversion
* LED-based signaling (dot and dash)
* Buzzer output with distinct tones for dots and dashes
* 16x2 I2C LCD display for message visualization
* Serial input support for dynamic messaging
* Continuous signal output (compatible with external visualization tools)

---

## Hardware Components

* ESP32
* 16x2 I2C LCD Display
* LEDs (for dot and dash indication)
* Piezo buzzer
* Jumper wires

---

## Pin Configuration

| Component        | ESP32 Pin |
| ---------------- | --------- |
| Dot LED (Blue)   | GPIO 2    |
| Dash LED (Green) | GPIO 5    |
| Buzzer           | GPIO 23   |
| LCD SDA          | GPIO 26   |
| LCD SCL          | GPIO 27   |

---

## Working Principle

1. User inputs a message via Serial input
2. The system converts each character into Morse code
3. Morse signals are transmitted through:

   * LED flashes (visual encoding)
   * Buzzer tones (auditory encoding)
4. The original message is displayed on the LCD
5. Signals are also sent via Serial for potential external visualization

---

## Installation & Setup

1. Connect all components as per the pin configuration
2. Install required libraries:

   * `Wire.h`
   * `LiquidCrystal_I2C.h`
3. Upload the code to ESP32 using Arduino IDE
4. Open Serial Monitor (9600 baud) to send messages

---

## Usage

* Enter any text in the Serial Monitor
* The system will:

  * Display the message on the LCD
  * Convert it into Morse code
  * Output signals via LED and buzzer

---

## Example

Input:
HELLO

Output:

* LCD displays: HELLO
* LED blinks Morse pattern
* Buzzer emits corresponding tones

---

## Author

Anwesha Rath
