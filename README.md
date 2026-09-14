# 🤖 Mecanum Wheel Robot

An Arduino-based 4WD omnidirectional robot using mecanum wheels, controlled via Bluetooth from a smartphone.

![Robot Demo](media/movement_demo.gif)

## 📋 Table of Contents

- [Features](#-features)
- [Components](#-components)
- [Wiring](#-wiring)
- [Code](#-code)
- [Bluetooth Commands](#-bluetooth-commands)
- [Setup Guide](#-setup-guide)
- [Movement Modes](#-movement-modes)
- [Troubleshooting](#-troubleshooting)
- [License](#-license)

---

## ✨ Features

- **Omnidirectional movement** — forward, backward, sideways, and diagonal
- **Bluetooth control** via HC-06 module
- **Simple command interface** — single letters from any Bluetooth terminal app
- **Constant full-speed operation** for maximum responsiveness
- **Mecanum wheel kinematics** implemented for all 6 movement types

---

## 🧰 Components

| Component | Quantity | Purpose |
| :--- | :--- | :--- |
| Arduino Uno | 1 | Main microcontroller |
| L293D Motor Driver Shield | 1 | Drives 4 DC motors |
| DC Motor with Mecanum Wheel | 4 | Omnidirectional movement |
| 4WD Robot Chassis | 1 | Frame |
| HC-06 Bluetooth Module | 1 | Wireless control |
| 11.1V 3S Li-ion Battery | 1 | Motor power |
| 1kΩ Resistor | 1 | Voltage divider |
| 2kΩ Resistor | 1 | Voltage divider |
| Jumper Wires | — | Connections |

---

## 🔌 Wiring

![Wiring Diagram](wiring/wiring_diagram.png)

### Quick Connection Table

| From | To | Notes |
| :--- | :--- | :--- |
| L293D Shield | Arduino Uno | Stack directly |
| Left Front Motor | M1 | Screw terminal |
| Left Back Motor | M2 | Screw terminal |
| Right Back Motor | M3 | Screw terminal |
| Right Front Motor | M4 | Screw terminal |
| Battery (+) | EXT_PWR | Screw terminal |
| Battery (−) | GND | Screw terminal |
| **PWR Jumper** | **REMOVED** | ⚠️ Critical |
| HC-06 VCC | 5V | — |
| HC-06 GND | GND | — |
| HC-06 TXD | A0 | — |
| HC-06 RXD | A1 | **Via voltage divider** |

### ⚠️ Voltage Divider (Required)

The HC-06 runs on 3.3V logic. Protect its RX pin:
