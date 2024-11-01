# BLE Gamepad Controller for ESP32 with ADXL345 Accelerometer

This project demonstrates how to create a Bluetooth Low Energy (BLE) gamepad using an ESP32 and an ADXL345 accelerometer. The ESP32 emulates a BLE gamepad, taking input from both an ADXL345 accelerometer (for motion-based control) and a joystick connected via an analog pin.

## Table of Contents
- [Features](#features)
- [Requirements](#requirements)
- [Setup](#setup)
- [Usage](#usage)
- [Connections](#connections)

## Features
- BLE HID gamepad emulation using the ESP32, which allows it to be recognized as a gamepad by devices like PCs and mobile phones.
- Motion controls using the ADXL345 accelerometer for directional inputs.
- Analog joystick support for button control.
- Predefined mappings for four buttons: A, B, C, and X.

## Requirements
- ESP32 development board
- ADXL345 accelerometer module
- Analog joystick
- Arduino IDE with the following libraries installed:
  - `BleConnectionStatus`
  - `BleGamepad`
  - `Wire`

## Setup

1. **Install Dependencies**: Ensure you have the necessary libraries installed in Arduino IDE:
   - Install `BleGamepad` library through the Library Manager in Arduino IDE.
   - Install `Wire` for I2C communication (pre-installed with Arduino IDE).

2. **Flash the Code**: Open the provided code in Arduino IDE, select the correct board and COM port, and upload the code to your ESP32.

## Usage

1. **Pairing the ESP32**: 
   - After uploading the code, power on the ESP32. 
   - Open Bluetooth settings on your target device, and pair with the ESP32 gamepad (it should appear as a HID device).
  
2. **Controls**:
   - **Joystick**: Moving the joystick triggers button presses based on the analog input.
   - **Accelerometer**: Tilting the ESP32 controls the directional pad.
     - Moving the ESP32 in different orientations will change directional input based on threshold values for x and y axes.
   - **Buttons**: A, B, C, and X buttons are mapped to GPIO pins for press and release functionality.

## Connections

### ESP32 and ADXL345 Wiring
- **ADXL345 (I2C Mode)**:
  - `SDA` -> GPIO 1
  - `SCL` -> GPIO 2
  - `VCC` -> 3.3V
  - `GND` -> GND

### ESP32 and Joystick
- **One analog input buttons**: Connect the analog output of the serial buttons to the specified ADC pin (set to pin `0` in the code).

## Code Highlights

- **ADXL345 Initialization**: The `initADXL345` function sets up the accelerometer in measurement mode with a full range of ±16g.
- **Accelerometer Data**: The `readAccelData` function reads x, y, and z axis data, converting raw values into acceleration (g values).
- **Joystick and Button Logic**: The loop reads analog input and checks the accelerometer for directional input based on the specified threshold.
