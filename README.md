# IoT_Based_Electricity_Theft_Detection

## Overview

This project uses an Arduino to detect power theft by measuring the differential current between two channels. It displays the current readings and differential voltage on an LCD. If power theft is detected, it triggers a relay to disconnect the power and sounds an alarm using a buzzer.

## Features

- **Current Measurement**: Measures current from two analog channels.
- **Differential Current Calculation**: Computes the differential current to detect power theft.
- **LCD Display**: Shows current readings and differential voltage.
- **Buzzer Alarm**: Sounds an alarm if power theft is detected.
- **Relay Control**: Disconnects the power when theft is detected.

## Components

- Arduino
- Liquid Crystal Display (LCD)
- Relay Module
- Buzzer
- Current Sensors
- Various resistors and capacitors for circuit stabilization

## Pin Configuration

### LCD Display

- `rs` (Pin 7)
- `en` (Pin 6)
- `d4` (Pin 5)
- `d5` (Pin 4)
- `d6` (Pin 3)
- `d7` (Pin 2)

### Sensors and Actuators

- `analogChannel1` (Analog Pin 0): First current sensor input.
- `analogChannel2` (Analog Pin 1): Second current sensor input.
- `BUZZER_PIN` (Pin 8): Buzzer output pin.
- `RELAY_PIN` (Pin 9): Relay control pin.

### Constants

- `sensitivity1` and `sensitivity2`: Sensitivity of the current sensors.
- `offsetVoltage1` and `offsetVoltage2`: Offset voltages for the current sensors.

## Code Explanation

### Libraries and Pin Definitions

```cpp
#include <LiquidCrystal.h>

// Pin Definitions
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
const int analogChannel1 = 0;
const int analogChannel2 = 1;
#define BUZZER_PIN 8
#define RELAY_PIN 9
```

### Sensor Parameters and Variables

```cpp
const int sensitivity1 = 100;
const int sensitivity2 = 100;
const int offsetVoltage1 = 2500;
const int offsetVoltage2 = 2500;

float adcValue1 = 0;
float adcValue2 = 0;
double voltage1 = 0;
double voltage2 = 0;
double current1 = 0;
double current2 = 0;
double differentialCurrent = 0;
```

### Setup Function

```cpp
void setup() {
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(RELAY_PIN, OUTPUT);
    lcd.begin(16, 2);

    lcd.setCursor(0, 0);
    lcd.print("Power Theft");
    lcd.setCursor(0, 1);
    lcd.print("   Detection");
    delay(2000);
    lcd.clear();
}
```

The `setup()` function initializes the LCD, buzzer, and relay. It displays an initial message on the LCD.

### Main Loop

```cpp
void loop() {
    unsigned int temp1 = 0;
    unsigned int temp2 = 0;
    float maxPoint1 = 0;
    float maxPoint2 = 0;

    // Read analog values and determine the maximum
    for (int i = 0; i < 500; i++) {
        temp1 = analogRead(analogChannel1);
        if (temp1 > maxPoint1) {
            maxPoint1 = temp1;
        }

        temp2 = analogRead(analogChannel2);
        if (temp2 > maxPoint2) {
            maxPoint2 = temp2;
        }
    }

    // Convert analog values to voltage
    adcValue1 = maxPoint1;
    voltage1 = (adcValue1 / 1024.0) * 5000;
    current1 = ((voltage1 - offsetVoltage1) / sensitivity1) / sqrt(2);

    adcValue2 = maxPoint2;
    voltage2 = (adcValue2 / 1024.0) * 5000;
    current2 = ((voltage2 - offsetVoltage2) / sensitivity2) / sqrt(2);

    // Calculate differential current
    differentialCurrent = voltage1 - voltage2;

    // Check for power theft
    if (differentialCurrent >= 50) {
        lcd.clear();
        delay(100);
        lcd.setCursor(0, 0);
        lcd.print(" POWER THEFT !!");
        lcd.setCursor(0, 1);
        lcd.print(" -Disconnected-");

        while (true) {
            digitalWrite(RELAY_PIN, HIGH);
            digitalWrite(BUZZER_PIN, HIGH);
            delay(1500);
            digitalWrite(BUZZER_PIN, LOW);
            delay(1000);
        }
    }

    // Display current readings and differential voltage
    lcd.setCursor(0, 0);
    lcd.print("I1=");
    lcd.print(current1, 2);
    lcd.print(" I2=");
    lcd.print(current2, 2);
    lcd.print("A");

    lcd.setCursor(0, 1);
    lcd.print("Vd=");
    lcd.print(differentialCurrent);

    delay(2500);
}
```

The `loop()` function reads the current values from the sensors, calculates the differential current, and displays the readings on the LCD. If power theft is detected, it triggers the relay and sounds the buzzer.

## Installation

1. **Hardware Setup**:
    - Connect the components to the Arduino as per the pin configuration.
    - Ensure the power supply to the sensors, buzzer, and relay is correctly set up.

2. **Software Setup**:
    - Install the necessary libraries in the Arduino IDE.
    - Open the `.ino` file in the Arduino IDE.
    - Upload the code to the Arduino board.

## Usage

1. Power on the system.
2. The LCD will display the current readings from the sensors.
3. If power theft is detected (differential current ≥ 50), the system will sound the buzzer and disconnect the power via the relay.

## Customization

- **Adjusting Sensitivity**: Modify `sensitivity1` and `sensitivity2` to match your current sensors' specifications.
- **Changing Detection Threshold**: Adjust the `if` condition for `differentialCurrent` to set a different threshold for power theft detection.
- **Changing in Pins**: Use the pins of LCD and ACS712 according to code provided.
- https://www.electronicshub.org/interfacing-acs712-current-sensor-with-arduino/

## Troubleshooting

- **LCD Not Displaying Properly**: Check the connections to the LCD and ensure the correct pins are defined in the code.
- **Incorrect Current Readings**: Verify the sensor connections and ensure the current sensors are functioning correctly.
- **Buzzer Not Sounding**: Check the connection to the buzzer and ensure it is properly connected to the defined pin.

## License

This project is licensed under the MIT License.

## Acknowledgments

Special thanks to the contributors of the libraries used in this project.
