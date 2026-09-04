# 🔐 Smart Door Security System

## 📌 Project Overview

An Arduino-based door security system that provides access through **password authentication using a 4×4 keypad** or **RFID card verification**. An **LCD** displays the system status, while **LEDs and a buzzer** provide visual and audible feedback during the authentication process.

## ⚙️ How It Works

* 🔑 The user enters a password using the keypad or scans an RFID card.
* 🔊 Each keypad press produces an audible feedback sound.
* 🟢 Successful authentication turns on the green LED and plays a confirmation sound.
* 🔴 Failed authentication turns on the red LED and plays an alert sound.
* 🖥️ The LCD displays the current access status and number of failed attempts.
* 🚨 After two incorrect password attempts, the system enters a temporary lockout mode.

## 📸 Project Gallery

### 01 — System Overview

Complete view of the Arduino-based security system.

![System Overview](Smart-Door-Security-System/images/1.jpeg)

### 02 — Password Input

The user enters the password using the keypad, with the digits hidden on the LCD.

![Password Input](Smart-Door-Security-System/images/2.jpeg)

### 03 — Access Denied

An incorrect password is detected and the first failed attempt is displayed.

![Access Denied](Smart-Door-Security-System/images/3.jpeg)

### 04 — System Locked

After two incorrect password attempts, the system temporarily locks access.

![System Locked](Smart-Door-Security-System/images/4.jpeg)

### 05 — Access Granted

The correct password is entered and access is successfully granted.

![Access Granted](Smart-Door-Security-System/images/5.jpeg)

### 06 — Card Verified

An authorized RFID card is successfully verified.

![Card Verified](Smart-Door-Security-System/images/6.jpeg)

### 07 — Invalid Card

An unauthorized RFID card is detected and access is denied.

![Invalid Card](Smart-Door-Security-System/images/7.jpeg)
