#ifndef SPIDERBOT_H
#define SPIDERBOT_H

#include <Servo.h>
#include <Wire.h>  // For MPU-6050
#include <NewPing.h>  // Ultrasonic sensor

class SpiderBot {
public:
  SpiderBot(int trigPin, int echoPin, int numServos = 12);
  void initServos();
  void setLegPosition(int leg, float x, float y, float z);  // IK solver
  void tripodGait(float speed);  // Alternating tripod walk
  bool detectObstacle();  // HC-SR04 check
  void gestureControl();  // MPU-6050 tilt-based movement

private:
  Servo servos[12];
  NewPing sonar;
  float legLengths[4];  // Coxa, femur, tibia per leg
  void inverseKinematics(int leg, float x, float y, float z, int& coxa, int& femur, int& tibia);
  void pidTune(float error);  // Simple PID for stability
};

#endif
