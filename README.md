## Project Overview
Effective waste management is a growing challenge in urban areas due to rapid population growth, overflowing waste bins, unhygienic environments, and inefficient waste collection systems. Traditional waste management approaches often rely on manual inspection and lack real-time monitoring, resulting in delayed waste collection and unnecessary maintenance efforts.

This project presents an **IoT-based Smart Dustbin** designed to automate waste monitoring and improve waste collection efficiency. The system uses an ESP32 microcontroller and ultrasonic sensors to detect user proximity, control the dustbin lid automatically, and monitor the waste fill level. When the bin reaches its maximum capacity, a real-time notification is sent to cleaning staff through Telegram, enabling timely waste collection.

## Key Features

- **Automatic Lid Control:** Detects approaching users and automatically opens the lid.
- **Real-Time Fill-Level Monitoring:** Measures the amount of waste inside the dustbin using an ultrasonic sensor.
- **Telegram Notifications:** Sends alerts to cleaning staff when the dustbin reaches its full capacity.
- **Contactless Operation:** Provides convenient and hygienic waste disposal.
- **IoT Integration:** Enables automated monitoring and communication through the internet.
- **Cost-Effective Design:** Uses affordable electronic components and a scalable architecture.

## Hardware Components

| Component | Function |
|---|---|
| ESP32 | Main microcontroller and IoT connectivity |
| HC-SR04 (Sensor 1) | User proximity detection |
| HC-SR04 (Sensor 2) | Waste fill-level measurement |
| SG90 Servo Motor | Automatic lid opening and closing |
| Smart Dustbin | Waste collection container |

## Working Principle

1. The proximity sensor continuously detects whether a user is approaching the dustbin.
2. When a user comes within the predefined detection range, the ESP32 activates the SG90 servo motor to open the lid.
3. After the user disposes of the waste, the lid automatically closes.
4. The second ultrasonic sensor continuously measures the distance between the sensor and the waste surface to estimate the bin's fill level.
5. When the waste reaches the predefined capacity threshold, the ESP32 sends a Telegram notification to the cleaning staff.
6. Cleaning personnel can empty the bin promptly, preventing waste overflow and maintaining a cleaner environment.

## Technologies Used

**Hardware:** ESP32, HC-SR04 Ultrasonic Sensors, SG90 Servo Motor

**Software & Communication:** Arduino IDE, Embedded C/C++, IoT, Telegram Bot API, Wi-Fi

## Project Benefits

- Reduces manual monitoring and intervention.
- Improves waste collection efficiency.
- Prevents overflowing bins and waste spillage.
- Promotes cleaner and healthier public environments.
- Enhances user convenience through contactless operation.
- Offers a scalable and affordable solution for smart city infrastructure.

## Potential Applications

The proposed system can be implemented in public parks, streets, educational institutions, shopping malls, hospitals, and other high-traffic urban locations.

## Project Objective

To develop a cost-effective and intelligent waste management solution that combines IoT technology, automated lid control, and real-time notifications to improve urban cleanliness and waste collection operations.
