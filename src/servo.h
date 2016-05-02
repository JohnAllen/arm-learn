#include <string>
#include <fstream>

#ifndef SERVO_COMMANDS_H
#define SERVO_COMMANDS_H


int calcTicks(float impulseMs, int hertz);
float map(float input, float min, float max);
float range_increment(float min, float max, float millis);
int angleMicroSec(int tick);
int resetServos();
int setServoMin(int num);
int servoAngle(int servo_num, int angle);
int incServo(int servo_num); 


#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50

const int SERVO_0 = 300;
const int SERVO_1 = 301;
const int SERVO_2 = 302;
const int SERVO_3 = 303;

const float MIN  = 0.6;
const float MAX = 2.4;

#define MIN_0 0.6
#define MAX_0 2.4
#define MIN_1 0.6
#define MAX_1 2.4
#define MIN_0 0.6
#define MAX_0 2.4
#define MIN_1 0.6
#define MAX_1 2.4

#endif

