#include "SpiderBot.h"
#include <MPU6050.h>  // Assume installed via Library Manager

MPU6050 mpu;

SpiderBot::SpiderBot(int trigPin, int echoPin, int numServos) : sonar(trigPin, echoPin, 200) {
  // Initialize leg lengths (in mm)
  for (int i = 0; i < 4; ++i) {
    legLengths[i] = 50.0;  // Example: adjustable
  }
}

void SpiderBot::initServos() {
  for (int i = 0; i < 12; ++i) {
    servos[i].attach(2 + i);  // Pins 2-13
    servos[i].write(90);  // Neutral position
  }
  Wire.begin();
  mpu.initialize();
}

void SpiderBot::setLegPosition(int leg, float x, float y, float z) {
  int coxa, femur, tibia;
  inverseKinematics(leg, x, y, z, coxa, femur, tibia);
  // Map to servo angles (0-180)
  int basePin = leg * 3;
  servos[basePin].write(coxa);
  servos[basePin + 1].write(femur);
  servos[basePin + 2].write(tibia);
}

void SpiderBot::tripodGait(float speed) {
  // Lift/move front-left/rear-right, then front-right/rear-left
  setLegPosition(0, 0, 50, 30);  // Example offsets; scale by speed
  delay(100 / speed);
  setLegPosition(2, 0, -50, 30);
  // PID correction for drift
  pidTune(0.1);  // Placeholder
}

bool SpiderBot::detectObstacle() {
  unsigned int distance = sonar.ping_cm();
  return (distance > 0 && distance < 20);  // Threshold in cm
}

void SpiderBot::gestureControl() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  float tiltX = atan2(ay, az) * 180 / PI;
  if (abs(tiltX) > 10) {
    tripodGait(abs(tiltX) / 10);  // Speed from tilt
  }
}

void SpiderBot::inverseKinematics(int leg, float x, float y, float z, int& coxa, int& femur, int& tibia) {
  // Simplified 3D IK (spherical coordinates)
  float r = sqrt(x*x + y*y + z*z);
  coxa = atan2(y, x) * 180 / PI + 90;  // Base rotation
  // Femur/tibia via law of cosines (omitted for brevity; implement full math)
  femur = 90;  // Placeholder
  tibia = 90;
}

void SpiderBot::pidTune(float error) {
  // Basic proportional control
  static float integral = 0;
  integral += error;
  float correction = 0.5 * error + 0.1 * integral;  // Kp, Ki
  // Apply to servo offsets
}
