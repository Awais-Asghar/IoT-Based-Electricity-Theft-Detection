# IoT Based Electricity Theft Detection System

![Project Status](https://img.shields.io/badge/Status-Completed-brightgreen.svg)
![Sensors](https://img.shields.io/badge/Sensors-ACS712%20%7C%20IR-yellow.svg)
![Platform](https://img.shields.io/badge/Platform-Arduino-blue.svg)
![Language](https://img.shields.io/badge/Language-C%2FC%2B%2B-pink.svg)
![IDE](https://img.shields.io/badge/IDE-Arduino%20IDE-purple.svg)
![License](https://img.shields.io/badge/License-MIT-lightgrey.svg)

<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/3178252b-430e-46e7-93bd-1a638cf1c700" />

---

## Introduction

Electricity theft is a major issue affecting power utilities and national economies. According to **Islamabad Times**, nearly **360 billion rupees worth of electricity was stolen in 2022-23**. This IoT-based solution detects unauthorized consumption by monitoring the current differential in a circuit using ACS712 sensors. If theft is detected, the system disconnects the power using a relay, activates a buzzer, and sends an SMS alert to the configured number via GSM.

<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/fad1df2b-4ed0-4536-8ab9-ac0189d1f4b7" />

<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/00cd670f-a2ca-4e39-b251-b378297905ae" />

<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/66f90eb5-4eb6-442e-90f1-d998fc5ff6ed" />

---

## Project Overview

This smart electricity meter is built using:

- **Arduino UNO**: Microcontroller for logic processing.
- **ACS712 Current Sensors**: Measure current at two different points.
- **LCD 16x2 Display**: Show current readings and alerts.
- **Relay Module**: Cuts off power if theft is detected.
- **Buzzer**: Audible alert on theft.
- **GSM Module**: Sends SMS to user (in expanded version).
- **Potentiometer (10k)**: Controls contrast for LCD.

The system compares two current values. If the difference exceeds a threshold, it assumes power is being illegally diverted.

---

## Features

- **Dual Current Monitoring** using ACS712 sensors  
- **Differential Current Detection** to spot theft  
- **Relay Cutoff + Buzzer Alarm** when theft is detected  
- **SMS Alert** via GSM module *(optional/expandable)*  
- **Real-Time LCD Display** of current values and theft status  
- **Auto Reset After Alert** (if desired via code update)

---

## Hardware Components

| Component             | Quantity |
|----------------------|----------|
| Arduino UNO          | 1        |
| ACS712 Current Sensor (20A) | 2        |
| LCD Display (16x2)   | 1        |
| Relay Module         | 1        |
| Buzzer               | 1        |
| GSM Module (SIM800L) | 1 *(optional)* |
| Potentiometer (10k)  | 1        |
| Jumper Wires         | -        |
| Breadboard/PCB       | 1        |
| Power Supply         | 1        |


<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/66f90eb5-4eb6-442e-90f1-d998fc5ff6ed" />

<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/0ebe5343-6a2f-46fb-a832-0530d02d4707" />

---

## Working Principle

1. The system constantly measures current from **two separate points** using **ACS712 sensors**.
2. If both values are close (within threshold), the system assumes **normal usage**.
3. If there's a **significant difference**, the system detects **power theft**.
4. On detection:
   - The **relay is triggered** to cut off power.
   - A **buzzer sounds** an alert.
   - A **message is sent** via GSM (if configured).

<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/ae69209f-5ab9-427f-807f-3ce30254bc9c" />

---

## Software Flow & Logic

<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/0ebe5343-6a2f-46fb-a832-0530d02d4707" />

### Working Logic

- **Read both sensors** and calculate current values
- **Compute differential current**
- If `differentialCurrent ≥ threshold (e.g., 50)`:
  - Display **“POWER THEFT”**
  - Trigger **relay + buzzer**
  - Optionally send **SMS alert**
- Else, display both currents and differential

---

### Pin Configuration

| Component         | Arduino Pin |
|------------------|-------------|
| LCD RS, E, D4-D7 | D7, D6, D5, D4, D3, D2 |
| ACS712 Sensor 1  | A0          |
| ACS712 Sensor 2  | A1          |
| Buzzer           | D8          |
| Relay            | D9          |
| GSM TX/RX        | D10/D11 *(if used)* |

---

## Code Summary

- **Libraries Used**: `LiquidCrystal`
- **Sensor Sensitivity**: 100mV/A
- **Voltage Reference**: 5V (5000 mV)
- **Offset Voltage**: 2500 mV (for both sensors)
- **RMS Calculation**: `(Vpeak - offset) / sensitivity / √2`

**> Ensure that ACS712 sensors are properly calibrated and isolated from mains supply!**

---

## Sample Output
LCD Display:
I1 = 2.55 I2 = 2.53 A
Vd = 0.02

OR

POWER THEFT !!
-Disconnected-

---

## SMS Alert Integration

To enable SMS alerts:

- Connect **SIM800L GSM module**
- Use `Serial` to send AT commands
- Configure destination number using `AT+CMGS`

Example:
```cpp
Serial.println("AT+CMGF=1");
Serial.println("AT+CMGS=\"+923XXXXXXXXX\"");
Serial.println("Power Theft Detected!");
```

## Future Enhancements

- Integrate **IoT Cloud Platform** (e.g., ThingSpeak, Blynk) for remote monitoring  
- Replace GSM with **Wi-Fi (ESP8266)** for real-time internet connectivity  
- Develop a **Mobile App Dashboard** for live data tracking  
- Incorporate **Machine Learning models** to analyze and predict theft behavior  
- Add an **Auto Reset Relay** function after theft alert acknowledgment  

<img width="2000" height="937" alt="Image" src="https://github.com/user-attachments/assets/0baee51b-7fa2-4824-846a-c62975bbbe59" />

---

## Applications

This system has wide-ranging real-world use cases, particularly in countries facing energy theft and distribution losses. Some of the key applications include:

- **Residential Electricity Monitoring**: Detect unauthorized connections or tampering in household energy usage.
- **Commercial & Industrial Energy Management**: Prevent illegal power usage in factories, shops, and commercial facilities.
- **Smart Grid Integration**: Can be scaled into smart grids for automated theft detection and control at the transformer/distribution level.
- **Utility Company Deployment**: Helps utility providers reduce revenue losses and monitor consumer integrity.
- **Educational & Research Projects**: Ideal for IoT, embedded systems, and energy efficiency-based academic research or student final-year projects.
- **Remote Locations Monitoring**: With GSM/WiFi integration, the system can operate in remote areas without physical inspection.
- **Tamper Detection in Prepaid/Postpaid Meters**: Add-on module to modern meters for enhanced security and power usage audit.

<img width="2000" height="937" alt="Image" src="https://github.com/user-attachments/assets/0baee51b-7fa2-4824-846a-c62975bbbe59" />

---


## Troubleshooting

| Issue                  | Solution                                  |
|------------------------|-------------------------------------------|
| LCD not displaying     | Check potentiometer setting and wiring    |
| No current reading     | Calibrate sensor, verify VCC & GND        |
| Relay not switching    | Confirm digital HIGH signal and connections |
| GSM not working        | Use active SIM, check signal & power supply |
| False theft alerts     | Tune or raise the differential threshold  |

---

## License

This project is licensed under the **MIT License**. Feel free to use, modify, and distribute it with proper attribution.

## Demo Video

https://github.com/user-attachments/assets/ea9b1b55-9d12-4969-9dc2-6b3e9aedabbd

---

## Remarks:
<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/f0e42e47-3107-4b80-853b-63f446625a0b" />
