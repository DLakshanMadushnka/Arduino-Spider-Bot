# Arduino Spider Bot

A quadruped robot with inverse kinematics and gesture control for educational prototyping.

## Hardware BOM
- Arduino nano: 1
- MG90 Servos: 12
- HC-SR04 Ultrasonic: 1
- MPU-6050 Accelerometer: 1
- Jumper Wires/Breadboard: Assorted

## Wiring
- See `schematics/SpiderBot.fzz` (Fritzing file).

## Installation
1. Install `NewPing` and `MPU6050` libraries via Arduino IDE.
2. Upload `BasicGait.ino`.
3. Calibrate servos via Serial Monitor.

## Advanced
- Add PCA9685 for 16+ servos: Modify `initServos()`.
- 3D Prints: Download STLs from [Thingiverse](https://www.thingiverse.com/thing:1234567).

## License
MIT
