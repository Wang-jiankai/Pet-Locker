# 🐾 Pet Locker

> MCU-based Pet Storage Locker — safe temporary housing for pets

[中文](README.md) · [📦 Software](#software) · [🔧 Hardware](#hardware) · [📋 Version Plan](#version-plan) · [🚀 Development Environment](#development-environment)

---

## 📌 Overview

As pet-friendly outings become more common, many venues restrict pet entry. This project is a **pet storage locker** controlled by a microcontroller:

- **Touchscreen** displays locker status and information input
- **Password** or **fingerprint** unlocks automatically
- **Temperature + sound sensors** detect abnormal body temperature or prolonged barking, send SMS alerts
- Escape or illness detected → immediate notification to owner

---

## ✨ Features

| Feature | Status |
|---------|--------|
| Touchscreen locker management | ✅ |
| Random password generation + SMS | ✅ |
| Infrared body temperature monitoring | ✅ |
| Barking / noise threshold alerts | ✅ |
| Fingerprint quick access | 🔜 |
| Face recognition payment | 🔜 |
| Custom PCB design | 🔜 |

---

## 📦 Software

**Source:** `1.Software/`

System status screens:

1. Locker selection screen
2. Phone number input screen
3. Password SMS sending screen
4. Password input screen
5. Payment screen

---

## 🔧 Hardware

Based on **STM32F1 Elite Development Board** + **2.8" TFTLCD** + **SIM900A** module.

Hardware resources in `2.Hardware/` — schematics, dimension drawings, and wiring diagrams.

---

## 📋 Version Plan

| Feature | Status |
|---------|--------|
| 10s idle → standby with ads | 🔜 |
| Infrared temperature measurement | ✅ |
| Continuous noise monitoring | ✅ |
| Sound level ADC | ✅ |
| SMS alerts (deposit/异常) | ✅ |
| Cat cage as locker unit | 🔜 |
| QR code payment after password | 🔜 |
| Face recognition payment | 🔜 |
| Fingerprint module | 🔜 |
| Owner fingerprint (open any cage) | 🔜 |
| Phone number stored in EEPROM | ✅ |
| Show stored phone during password input | ✅ |
| Door motor + driver module | ✅ |
| Custom PCB | 🔜 |

---

## 🚀 Development Environment

MDK 5.14.0.0

---

## 📂 Directory Structure

```
Pet-Locker/
├── 1.Software/             # Firmware source
├── 2.Hardware/             # Hardware resources (schematics, wiring diagrams)
├── README.md               # Chinese version
└── README_EN.md            # English version
```

---

## 🔄 Changelog

### 3.0_Full_Version

- Password included in SMS for real-time access
- Pet temperature anomaly triggers alert SMS (no repeat within 10 min)
- Door motor added (relay controlled)
- Microphone upgraded to more sensitive model
- Locker 16 pet data + unit name displayed in real-time

### 2.4_Preview

- Infrared temperature measurement implemented
- Temperature data shown on homepage per locker

### 2.3_Preview

- SMS sent after phone confirmation (password in SMS pending)
- Auto alert SMS when continuous barking detected (no repeat within 15 min)
- Other refinements

### 2.2_Preview

- 11-digit phone number saved to EEPROM, deleted on pickup
- Phone number shown then wiped after pet retrieval
- SIM900A software configured
- Screen returns home + buzzer after payment
- Shows stored phone during password input

### 2.1_Preview

- SIM module hardware/software tested
- MIC on Locker 16 detects noise level and displays it
- MIC threshold trigger SMS
- Infrared temperature module (integration pending)

### 2.0_Preview

- Password changed to random generation, saved to EEPROM
- Code comments improved
- Touchscreen calibration
- Locker vacancy flag saved to EEPROM
- Pet deposit timestamp saved to EEPROM
- Fee calculation based on storage duration
- Delete button supports back to previous screen
- Debug buzzer for noise calibration
- Full workflow completed, mid-term defense passed

---

## 🤝 Contributing

1. Fork this repo
2. Create a `Feat_xxx` branch
3. Commit your changes
4. Open a Pull Request

---

## ⭐ Star History

[![Star History Chart](https://api.star-history.com/image?repos=Wang-jiankai/Pet-Locker&type=date&legend=top-left)](https://www.star-history.com/#Wang-jiankai/Pet-Locker&type=date)
