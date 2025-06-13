# Automated Color Sorting Machine
#### Author: Bocaletto Luca

**Files**  
- `README.md`  
- `ColorSorter.ino`

## 1. Concept  
A bench-top machine that detects an object on a conveyor (or platform), reads its color, then flips a servo-actuated gate to route the part into one of three bins: Red, Green, or Blue.

**Workflow**  
1. Ultrasonic sensor senses object arrival.  
2. TCS34725 color sensor reads RGB values.  
3. MCU classifies dominant color.  
4. Servo moves to one of three positions.  
5. Gate returns to neutral, ready for next part.

## 2. Bill of Materials  
- 1 × Arduino Uno (or Nano)  
- 1 × Adafruit TCS34725 Color Sensor (I²C)  
- 1 × HC-SR04 Ultrasonic Distance Sensor  
- 1 × SG90 Servo Motor  
- 1 × Breadboard + jumper wires  
- 1 × 5 V power supply (USB or external)  

## 3. Wiring Diagram

      Arduino Uno                    Module/Actuator
      ┌────────────────┐             ┌──────────────┐
      │ 5 V ──────────► VCC            │ HC-SR04      │
      │ GND ──────────► GND            │ HC-SR04      │
      │ D9  ──────────► Trig           │ HC-SR04      │
      │ D10 ──────────► Echo           │ HC-SR04      │
      ├────────────────┤             
      │ A4  ──────────► SDA            │ TCS34725     │
      │ A5  ──────────► SCL            │ TCS34725     │
      │ 5 V ──────────► VIN            │ TCS34725     │
      │ GND ──────────► GND            │ TCS34725     │
      ├────────────────┤             
      │ D6  ──────────► PWM            │ SG90 Servo   │
      │ 5 V ──────────► VCC            │ SG90 Servo   │
      │ GND ──────────► GND            │ SG90 Servo   │
      └────────────────┘              └──────────────┘

> Place parts so that each object passes directly over the TCS34725 window and within 5 cm of the HC-SR04.

## 4. Software Setup  
1. In Arduino IDE install libraries:  
   - **Adafruit TCS34725**  
   - **Adafruit BusIO**  
   - **Servo** (built-in)  
2. Create a sketch folder named `ColorSorter` and save `ColorSorter.ino` inside.  
3. Upload to Arduino.

## 5. Operation  
- Place an object on the platform.  
- Wait for the servo to route it into Red, Green, or Blue bin.  
- Repeat!

---

Say **continua** to move on to project #4.  
