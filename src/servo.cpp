#include "servo.h"
#include <fstream>
#include <iostream>
#include <wiringPi.h>
#include <pca9685.h>
#include <string>
#include <boost/filesystem.hpp>
#include "../../raspicam/src/raspicam_still.h"

/**
 *  *  *  * Calculate the number of ticks the signal should be high for the required amount of time
 *   *   *   */

int PIN_NUMS[4] = {SERVO_0, SERVO_1, SERVO_2, SERVO_3};

using namespace std;
using namespace boost::filesystem;
using namespace boost::system;


int calcTicks(float impulseMs, int hertz)
{
    float cycleMs = 1000.0f / hertz;
    return (int)(MAX_PWM * impulseMs / cycleMs + 0.5f);
}

float map(float input, float min, float max)
{
    return (input * max) + (1 - input) * min;
}

float range_increment(float min, float max, float millis)
{
    return (max - min) / millis;
}

int angleMicroSec(int tick)
{
    return tick;
}

int servoAngle(int servo_num, int angle)
{
    float angleRange = 180;
    float servoRange = MAX - MIN;
    float anglePercent = angle / angleRange;
    float servoAngle = MIN + (anglePercent * servoRange);
    int tick = calcTicks(servoAngle, HERTZ);
    pwmWrite(servo_num, tick);
}

int resetServos()
{
    int i;
    for (i = 0; i < sizeof(PIN_NUMS); i++)
    {
        cout << "turning off servo with pin: " << PIN_NUMS[i] << endl;
        setServoMin(PIN_NUMS[i]);
    }
}

int setServoMin(int num)
{
    int tick = calcTicks(.6, HERTZ);
    pwmWrite(num, tick);
    return 0;
}

