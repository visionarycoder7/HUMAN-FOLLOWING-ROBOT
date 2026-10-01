# HUMAN-FOLLOWING-ROBOT
# Human Following Robot using Arduino UNO

A smart **Human Following Robot** built using **Arduino UNO**, **L298N Motor Driver**, **HC-SR04 Ultrasonic Sensor**, **Dual IR Sensors**, **SG90 Servo Motor**, and a **0.96" OLED Display**. The robot follows a nearby person or object, scans its surroundings using a servo-mounted ultrasonic sensor, and displays the measured distance on the OLED.

---

## 📌 Features

- 🤖 Human/Object Following
- 📏 Real-time Distance Measurement
- 🔄 Servo-based Ultrasonic Scanning
- 📺 OLED Distance Display
- 🚗 Differential Drive using 4 BO Motors
- ⚡ PWM Speed Control
- 🛑 Automatic Stop at Minimum Distance
- ↩️ Automatic Left/Right Turning using IR Sensors

---

## 📷 Project Overview

The robot continuously measures the distance to the object in front using the HC-SR04 ultrasonic sensor. Two IR sensors detect whether the target is slightly left or right. Based on this information, the robot adjusts its movement to follow the target while maintaining a safe distance.

The ultrasonic sensor is mounted on an SG90 servo motor, enabling left-center-right scanning whenever the target is lost or an obstacle is encountered. The measured distance is displayed in real-time on the OLED display.

---

# Hardware Components

| Component | Quantity |
|-----------|---------:|
| Arduino UNO | 1 |
| L298N Motor Driver | 1 |
| HC-SR04 Ultrasonic Sensor | 1 |
| SG90 Servo Motor | 1 |
| SSD1306 OLED Display (0.96") | 1 |
| IR Obstacle Sensors | 2 |
| BO Motors | 4 |
| Robot Chassis | 1 |
| Wheels | 4 |
| 18650 Batteries | 2–3 |
| Buck Converter (Servo Power) | 1 |
| Jumper Wires | As Required |

---

# Circuit Connections

## Arduino UNO

| Arduino Pin | Connected To |
|-------------|--------------|
| D2 | Left IR Sensor |
| D3 | Servo Signal |
| D4 | Right IR Sensor |
| D5 | ENA (L298N) |
| D6 | ENB (L298N) |
| D7 | IN1 |
| D8 | IN2 |
| D9 | IN3 |
| D10 | IN4 |
| D11 | Ultrasonic TRIG |
| D12 | Ultrasonic ECHO |
| A4 | OLED SDA |
| A5 | OLED SCL |
| 5V | OLED & Sensors |
| GND | Common Ground |

---

## L298N Connections

### Right Motors

```
OUT1 → Red Wire
OUT2 → Black Wire
```

### Left Motors

```
OUT4 → Red Wire
OUT3 → Black Wire
```

> **Note:** The left motor polarity was reversed to match the correct forward direction.

---

## Servo Connections

| Servo Wire | Connection |
|------------|------------|
| Signal | Arduino D3 |
| VCC | Buck Converter 5V Output |
| GND | Buck Converter GND |

---

## Ultrasonic Sensor

| HC-SR04 | Arduino |
|----------|---------|
| VCC | 5V |
| GND | GND |
| TRIG | D11 |
| ECHO | D12 |

---

## OLED Display

| OLED | Arduino |
|------|---------|
| VCC | 5V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

---

## Power Supply

### Battery Pack

- 2 × 18650 Batteries (Recommended)
- 3 × 18650 Batteries (Higher Speed)

Battery Positive

```
Battery +
     |
     +-----> L298N VIN
     |
     +-----> Buck Converter IN+
```

Battery Negative

```
Battery -
     |
     +-----> L298N GND
     |
     +-----> Buck Converter IN-
```

### Buck Converter Output

```
OUT+ → Servo VCC
OUT- → Servo GND
```

All grounds must be connected together.

---

# Software Requirements

- Arduino IDE
- Arduino UNO Board Package

---

## Required Libraries

Install the following libraries using the Arduino Library Manager:

- Servo
- Adafruit GFX
- Adafruit SSD1306

---

# Working Principle

1. The HC-SR04 measures the distance to the object.
2. The OLED displays the measured distance.
3. If the object is between the minimum and maximum distance:
   - The robot moves forward.
4. If the left IR sensor detects the object:
   - The robot turns left.
5. If the right IR sensor detects the object:
   - The robot turns right.
6. If the object is too close:
   - The robot stops.
7. If no object is detected:
   - The servo scans left and right.
   - The robot turns toward the direction with greater free space.

---

# Pin Configuration

```cpp
#define LEFT_IR 2
#define SERVO_PIN 3
#define RIGHT_IR 4

#define ENA 5
#define ENB 6

#define IN1 7
#define IN2 8

#define IN3 9
#define IN4 10

#define TRIG 11
#define ECHO 12
```

---

# Motor Speed

```cpp
#define MOTOR_SPEED 255
#define TURN_SPEED 200
```

PWM Range

```
0 - 255
```

---

# Future Improvements

- ESP32-CAM Human Detection
- Bluetooth Manual Control
- Voice Commands
- Gesture Recognition
- Obstacle Avoidance
- Line Following Mode
- Mobile App Control
- Battery Voltage Monitoring
- Automatic Charging Dock

---

# Applications

- Personal Assistant Robot
- Smart Shopping Cart
- Warehouse Automation
- Object Following Robot
- Educational Robotics
- Human Assistance Robot
- Indoor Navigation

---

# Folder Structure

```
Human-Following-Robot/
│
├── Human_Following_Robot.ino
├── README.md
├── images/
│   ├── robot.jpg
│   ├── circuit.jpg
│   └── wiring.jpg
└── LICENSE
```

---

# Author

**Sohan Ghosh**

B.Tech Electronics & Communication Engineering

Cooch Behar Government Engineering College

---

# License

This project is released under the **MIT License**. Feel free to modify, use, and distribute it for educational and personal projects.

---

## Acknowledgements

- Arduino Community
- Adafruit
- Open Source Hardware Community
- Electronics Hobbyist Community

⭐ If you found this project useful, consider giving it a star on GitHub!
