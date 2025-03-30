# Arduino Alarm System

This project implements an Arduino-based alarm system with multiple alarms for different days of the week. It uses a real-time clock (RTC), a buzzer for sound notifications, and an LCD display to show the current time and active alarms. The alarm times are pre-defined for weekdays, weekends, and Wednesdays.

## Components Used
- **Arduino Board (Arduino Uno)**
- **DS1307 RTC Module**: Used to keep track of time.
- **LiquidCrystal LCD Display (16x2)**: Used to display the current time and day of the week.
- **Buzzer**: Used to sound the alarm.
- **Push Button**: Used to manually trigger the alarm.

## Libraries
This project uses the following Arduino libraries:
- **Wire.h**: For I2C communication with the RTC.
- **TimeLib.h**: To handle time functions.
- **DS1307RTC.h**: For interfacing with the DS1307 RTC module.
- **LiquidCrystal.h**: For controlling the LCD.

## Pin Configuration
- **RTC SDA (Data Pin)**: A4
- **RTC SCL (Clock Pin)**: A5
- **Buzzer Pin**: 6
- **LCD Pins**:
  - RS: 12
  - EN: 11
  - D4: 5
  - D5: 4
  - D6: 3
  - D7: 2
- **Button Pin**: 13

## Features
- **Multiple Alarms**: Set up to 16 alarms with configurable times for different days of the week.
- **Sound Alarm**: The buzzer will sound when an alarm is triggered.
- **LCD Display**: Shows the current time and the day of the week on a 16x2 LCD screen.
- **Button**: Press the button to manually trigger the alarm.

## Alarm Schedule
- **Weekdays (Monday to Friday)**: A set of alarms at predefined times.
- **Weekend (Saturday & Sunday)**: A different set of alarms.
- **Wednesday**: Custom alarm schedule for Wednesdays.

## How It Works
- The system initializes the RTC, sets the alarm times based on the current day, and displays the time and day of the week on the LCD.
- When the system detects the current time matches any active alarm, it will trigger the buzzer.
- A button can be used to manually sound the alarm at any time.

## How to Use
1. Upload the code to your Arduino board.
2. Connect the components as per the pin configuration.
3. The system will initialize, display "Alarm System Initialized" on the LCD, and then continuously show the current time and day.
4. The buzzer will sound when an alarm time is reached, and the user can press the button to trigger the alarm manually.

## Installation
1. Download the necessary libraries (`Wire`, `TimeLib`, `DS1307RTC`, `LiquidCrystal`) through the Arduino IDE Library Manager.
2. Upload the sketch to your Arduino board.
3. Connect the components as specified in the pin configuration.

## License
This project is open-source. Feel free to modify and use it for your own projects!

---

### Created by [Kirenga Danick](https://github.com/kdanick)
