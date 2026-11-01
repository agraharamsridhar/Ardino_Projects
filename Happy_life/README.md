# Happy Life

## Project Description

This project is a small Arduino-based time awareness device created to remind the user that time is limited and to encourage living each day with purpose.

The idea is simple: the device shows the current time and date, and also tracks the number of days and weeks remaining. It helps the user stay conscious of how time is passing and makes every moment feel more meaningful.

The core goal is:

- Be in control of your own time
- Use time wisely
- Value each moment
- Live intentionally

This project is not just a clock; it is a reminder that life is short and every day matters.

## Components Used

1. Arduino Nano
   - The main microcontroller board
   - Controls the logic, reads RTC data, updates the display, and manages EEPROM storage

2. DS3231 Real-Time Clock (RTC)
   - Keeps accurate date and time even when the Arduino is powered off
   - Used to trigger daily alarms and track when a day changes

3. TM1637 4-Digit Display
   - Displays time, date, and remaining values like days/weeks
   - Commonly used in compact, low-power Arduino projects

4. EEPROM Memory
   - Stores the remaining day and week counters even after power loss
   - Prevents the countdown from resetting every time the device turns off

5. Wires, breadboard, and power connection
   - Used to connect the modules to the Arduino
   - Allows communication between the controller and hardware modules

## Why This Project Is Useful

This project combines timekeeping with a personal reminder system. It can be used as:

- a daily countdown device
- a time awareness display
- a reminder for living intentionally
- a simple hardware project that blends electronics and daily motivation

## Pin Connections

### Arduino Nano to DS3231 RTC

- A4 (SDA) -> RTC SDA
- A5 (SCL) -> RTC SCL
- 5V -> RTC VCC
- GND -> RTC GND
- D2 -> SQW/INT (alarm interrupt pin)

### Arduino Nano to TM1637 4-Digit Display

- D4 -> CLK
- D5 -> DIO
- 5V -> VCC
- GND -> GND

### Wiring Summary

```
Arduino Nano          DS3231 RTC
--------------------------------
A4                   SDA
A5                   SCL
5V                   VCC
GND                  GND
D2                   SQW/INT

Arduino Nano          TM1637 Display
--------------------------------
D4                   CLK
D5                   DIO
5V                   VCC
GND                  GND
```

## How the System Works

1. The Arduino starts and initializes the display and RTC module.
2. It reads saved values from EEPROM.
3. The RTC keeps current time and date.
4. A daily alarm triggers at midnight or when the day changes.
5. On each alarm, the program decreases the remaining days counter.
6. If the day is Monday (or a chosen day), the weeks counter also decreases.
7. The updated values are written back to EEPROM so they remain saved.
8. The display cycles through:
   - current time
   - current date
   - remaining days
   - remaining weeks

## File Explanation

### 1. main.ino
This is the main project file. It contains the actual logic of the device.

Responsibilities:

- includes required libraries
- creates the RTC object
- initializes the display
- reads saved data from EEPROM
- configures the alarm interrupt
- updates the 4-digit display in sequence
- decreases day and week counters when the alarm is triggered
- writes the new values back to EEPROM

This is the most important file because it controls the complete behavior of the device.

### 2. Setup_RTC.ino
This file is used to set the RTC clock for the first time.

Responsibilities:

- starts the serial communication
- initializes the I2C bus
- lets the user send a command like 'C' to set the clock
- sets the year, month, date, day, hour, minute, and second
- prints the current date and time continuously

This file is useful when the RTC has not been configured yet or when the time needs to be corrected.

### 3. Setup_EEPROM.ino
This file is used to initialize the EEPROM memory.

Responsibilities:

- clears all memory locations in EEPROM
- writes the initial stored values using `EEPROM.put()`
- stores starting values for remaining days and weeks

This is usually a one-time setup script used before running the main project.

### 4. README.md
This file explains the purpose of the project, its hardware, wiring, workflow, and files.

It acts as the documentation for the entire directory.

## Project Flow

- First, use `Setup_EEPROM.ino` to initialize memory
- Then use `Setup_RTC.ino` to set the correct current time and date
- Finally upload `main.ino` to run the full project

## Notes

- `EEPROM` is used so the values remain even after power loss.
- The DS3231 RTC is useful because it keeps time accurately without depending on the Arduino clock.
- The alarm interrupt allows the program to react when the date changes, making the countdown behavior automatic.
- The display is used to show information in a very compact and readable format.

## Summary

This directory contains a complete Arduino project that turns time into a visible, daily reminder. It shows the user what time it is and how much time is left, turning a simple electronics setup into a meaningful project about consciousness, life, and time management.

The project can be described as:

- a real-time clock system
- a countdown tracker
- a personal life reminder device
- a practical electronics project built with Arduino

# End of Project Documentation
