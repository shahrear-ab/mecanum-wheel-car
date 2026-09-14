# 🤖 Mecanum Wheel Robot

An Arduino-based 4WD omnidirectional robot using mecanum wheels, controlled via Bluetooth from a smartphone.

![Robot Demo](media/movement_demo.gif)

---

## ✨ Features

- Omnidirectional movement — forward, backward, sideways, and diagonal
- Bluetooth control via HC-06 module
- Adjustable speed control (8 presets + incremental)
- Simple single-letter command interface

---

## 🧰 Components

| Component | Quantity |
| :--- | :--- |
| Arduino Uno | 1 |
| L293D Motor Driver Shield | 1 |
| DC Motor with Mecanum Wheel | 4 |
| 4WD Robot Chassis | 1 |
| HC-06 Bluetooth Module | 1 |
| 11.1V 3S Li-ion Battery | 1 |
| 1kΩ + 2kΩ Resistors | 1 each |
| Jumper Wires | — |

---

## 🔌 Wiring

| From | To |
| :--- | :--- |
| L293D Shield | Stack on Arduino Uno |
| Left Front Motor | M1 |
| Left Back Motor | M2 |
| Right Back Motor | M3 |
| Right Front Motor | M4 |
| Battery (+) | EXT_PWR |
| Battery (−) | GND |
| **PWR Jumper** | **REMOVED** ⚠️ |
| HC-06 VCC | 5V |
| HC-06 GND | GND |
| HC-06 TXD | A0 |
| HC-06 RXD | A1 (via voltage divider) |

### Voltage Divider (Required for HC-06 RXD)


A1 ──[1kΩ]──┬── HC-06 RXD
│
[2kΩ]
│
GND



---

## 💻 Code

File: [`Arduino_Mecanum_RC_Car.ino`](Arduino_Mecanum_RC_Car.ino)

**Required Library:** Adafruit Motor Shield V1 Library
> ⚠️ Do NOT use the R4 version — it will cause compile errors.

Install via: **Sketch → Include Library → Manage Libraries → Search "Adafruit Motor Shield V1"**

---

## 📱 Bluetooth Commands

| Key | Action | Key | Action |
| :--- | :--- | :--- | :--- |
| `F` | Forward | `G` | Diagonal Forward-Left |
| `B` | Backward | `I` | Diagonal Forward-Right |
| `L` | Turn Left | `H` | Diagonal Backward-Left |
| `R` | Turn Right | `J` | Diagonal Backward-Right |
| `Q` | Strafe Left | `E` | Strafe Right |
| `S` | Stop | `+` / `-` | Speed up / down |
| `0`–`7` | Set speed (100–255) | | |

**App:** BlueBot / Serial Bluetooth Terminal
**Baud:** 9600 | **PIN:** `1234` or `0000`

---

## 🚀 Setup Guide

1. Stack L293D shield on Arduino Uno
2. Connect motors to M1–M4
3. Remove PWR jumper
4. Connect battery to EXT_PWR + GND
5. Wire HC-06 with voltage divider
6. Install AFMotor V1 library
7. Upload `Arduino_Mecanum_RC_Car.ino`
8. Power Arduino via USB or 9V
9. Pair phone with HC-06, open app
10. Send `F` to test

---

## ⚠️ Safety Notes

- **Never** connect 11.1V battery to Arduino 5V pin
- **Always** remove the PWR jumper
- Power Arduino separately (USB or 9V)
- If a motor spins wrong direction, swap its two wires

---

## 🐛 Troubleshooting

| Problem | Fix |
| :--- | :--- |
| Only one motor spins | Check PWR jumper removed |
| Motor spins wrong way | Swap motor wires |
| Bluetooth won't connect | Check A0/A1 wiring, PIN `1234` |
| Compile error `MOTOR12_1KHZ` | Install AFMotor **V1**, not R4 |
| Diagonal not working | Adjust `speed_reducing_factor` |

---

## 📜 License

MIT License — see [LICENSE](LICENSE)

---

⭐ If this helped you, give it a star!
