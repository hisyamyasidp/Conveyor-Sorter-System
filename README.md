# Conveyor-Sorter-System

---

**Conveyor Sorter System** is an automated material handling simulation based on Arduino. The system utilizes a conveyor belt to transport items, an analog sensor to detect color properties (simulated via ADC), and dual servo actuators to sort items into designated paths. This project was designed and tested using the **Tinkercad** simulation environment.

---

## Pin Configuration

| Component | Arduino Pin | Description | Power Connection |
| :--- | :---: | :--- | :--- |
| **LCD 16x2 I2C** | **A4 (SDA), A5 (SCL)** | System Monitoring | 5V & GND |
| **Potentiometer** | **A0** | Color Sensor Simulation | 5V & GND |
| **Push Button Start** | **D2** | System Start (Input Pull-up) | GND |
| **Push Button Stop** | **D3** | Stop / Reset EMG (Input Pull-up)| GND |
| **Push Button EMG** | **D4** | Emergency Stop (Input Pull-up) | GND |
| **NeoPixel Ring** | **D6** | LED Visual Indicators | 5V & GND |
| **L293D (Input 2)** | **D7** | Motor Direction B | - |
| **L293D (Input 1)** | **D8** | Motor Direction A | - |
| **L293D (Enable 1)** | **D9** | Speed Control (PWM) | - |
| **Servo Red** | **D10** | Red Sorting Actuator | 5V & GND |
| **Servo Green** | **D11** | Green Sorting Actuator | 5V & GND |

---

## Operational Workflow

1. **Startup:** Press **Start** to initiate the conveyor. The motor runs at a calibrated slow speed, and the NeoPixel displays a rotating blue animation.
2. **Detection:** Adjust the potentiometer to simulate object detection (100-400 for Red, 600-900 for Green).
3. **Sorting Process:** Once an object is detected, the conveyor continues for a short delay to ensure the object reaches the gate, then stops. The corresponding servo moves 90° to sort the item.
4. **Emergency Mode:** Pressing the **EMG** button instantly halts all operations. The NeoPixel flashes red rapidly. Press **Stop** to reset and return to standby.

---

## Project Documentation
* **Source Code:** [Code.ino](https://github.com/hisyamyasidp/Conveyor-Sorter-System/blob/main/Code.ino)
* **Circuit Schematic:** [3D Schematics](https://github.com/hisyamyasidp/Conveyor-Sorter-System/blob/main/3d%20Scematics.png)
* **Simulation Video:** [Video Simulation](https://github.com/hisyamyasidp/Conveyor-Sorter-System/blob/main/Video%20Simulation.webm)
* **TinkerCad:** [Try On Tinker](https://www.tinkercad.com/things/3avvur9WUcC-hisyam-yasidconveyor-sorter-system)

---
*Developed by [Hisyam Yasid Pratowo](https://github.com/hisyamyasidp)*
