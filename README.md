# Alphanumeric Keypad Interfacing with 8051

## Introduction
This project implements an alphanumeric keypad, similar to the ones found in mobile phones, using an 8051 microcontroller. The system allows users to input alphanumeric characters and provides a visual display on an LCD.

## Objective
The primary objectives of the project are:
- Develop a functional alphabetical keypad interface.
- Implement interrupt-driven functionalities for clearing the screen and backspacing.
- Display entered characters on an LCD.

## Application
The alphanumeric keypad interfacing system is designed with versatility in mind, providing an efficient and user-friendly input interface for a range of applications. This system can be used for text entry, embedded system control, data logging, or as a user interface for various devices.

## Block Diagram
The system comprises:
- **Microcontroller (8051)**: Processes key presses and displays them.
- **LCD Display**: Shows the entered characters.
- **4x3 Keypad**: Used for alphanumeric input.
- **Clear Screen and Backspace Buttons**: Implemented for special functions.

## Design Methodology

### Keypad Interface
The keypad is connected to Port 1 of the 8051 microcontroller. Rows are connected to `P1^0` to `P1^3`, and columns are connected to `P1^4` to `P1^6`. The microcontroller scans the keypad to detect key presses.

### LCD Interface
The LCD is connected to Port 3. Data lines connect to `P3^5`, `P3^6`, and `P3^7`, while control lines (RS, RW, EN) are connected to `P3^5`, `P3^6`, and `P3^7`. Commands and data are sent via the `lcdcmd` and `lcddata` functions.

### Interrupts
Two external interrupts (`INT0` and `INT1`) handle special functions:
- **Clear Screen**: Clears the display.
- **Backspace**: Deletes the last entered character.

## Components

### Hardware Components
- 8051 Microcontroller
- 4x3 Matrix Keypad
- LCD Display
- Push Buttons (Clear Screen and Backspace)

### Software Components
- Keil uVision5
- Embedded C Language
- LCD Control Functions (`lcdcmd`, `lcddata`)
- Interrupt Service Routines (`clearScreenISR`, `backspaceISR`)
- Main program logic for keypad scanning and LCD display

## Code Structure

### Initialization and Pin Definitions
Defines pins for keypad rows, columns, and LCD data/control pins. It also initializes variables for tracking inputs and cursor positions.

### Interrupt Service Routines (ISRs)
- **clearScreenISR**: Clears the screen and resets the cursor.
- **backspaceISR**: Deletes the last entered character.

### Main Program

1. **LCD Initialization**: Sets up the LCD for a two-line display.
2. **Interrupt Setup**: Configures `INT0` and `INT1` for the clear screen and backspace buttons.
3. **Keypad Scanning Loop**: Continuously scans the keypad for input.
4. **Key Press Handling**: Updates the display or performs actions based on key presses.
5. **Line Management**: Manages the transition to the next line on the LCD when the current line is filled.

### Display Functions
- **num_check**: Checks and resets keypress count.
- **repeat**: Adjusts character count for repeated key presses.
- **display**: Maps keys to characters and updates the LCD.

### LCD Control Functions and Delay
- **lcdcmd**: Sends control commands to the LCD.
- **lcddata**: Sends data for display.
- **delay**: Adds a time delay.

### Clear Screen Function
- **clearScreen**: Clears the display and resets the cursor.

## User Manual: Alphanumeric Keypad Interface

### Normal Character Input
Press keys multiple times to cycle through characters (e.g., pressing `1` cycles through `a`, `b`, `c`, and `1`).

### Special Actions
- **Backspacing**: Press the backspace button to delete the last character.
- **Clearing the Screen**: Press the clear screen button to reset the display.
- **Saving a Character**: Press `*` to save a character at the cursor position.
- **Moving to the Next Line**: Press `#` to move to the next line on the LCD.

### Tips for Efficient Use
- **Use Multiple Keypresses**: Familiarize yourself with character sequences.
- **Monitor Cursor Position**: Watch the cursor to see where the next character will appear.

## Results
The system successfully recognizes key presses and displays characters on the LCD. Interrupt-driven functionalities for clearing the screen and backspacing enhance user convenience.

## Challenges
The development process involved several challenges:
- **Interrupt Usage**: Initial use of interrupts for delays increased hex file size, requiring alternative timing methods.
- **Port Limitations**: Direct use of Port 0 for backspace and clear functions introduced delays, leading to interrupt-based solutions and debounce circuits.

## Conclusion
The implemented alphanumeric keypad system demonstrates effective integration of a microcontroller, keypad, and LCD display. Interrupts enable additional functionalities, making the system user-friendly and functional.

## Future Enhancements
- Add text editing functions.
- Increase functionality with more buttons.
- Improve user interface for intuitive interaction.
- Optimize code for better performance.
