#include <stdio.h>
#include "../../raspicam/src/raspicam_still.h"
#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <wiringPi.h>
#include <pca9685.h>
#include <fstream>
#include <ctime>
#include <string>
#include <chrono>

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50

#define SERVO_0 300 // pan
#define SERVO_1 301
#define SERVO_2 302
#define SERVO_3 303 

#define MIN_0 0.6
#define MAX_0 2.4
#define MIN_1 0.6
#define MAX_1 2.4
#define MIN_2 0.6
#define MAX_2 2.4
#define MIN_3 0.6
#define MAX_3 2.4

using namespace std;
const int TASK_TIME_LIMIT_SECS = 20;

/**
 *  *  * Calculate the number of ticks the signal should be high for the required amount of time
 *   *   */
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


int main ()
{
    // required by ncurses.h; inits key read
    int TASK_ATTEMPT_DURATION_SECS = 0;
    
    cout << "Beginning" << endl;
    
    int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
    
    if (fd < 0) {
        printf("Error in setup\n");
        return fd;
    }
    
    pca9685PWMReset(fd);
    
    int tick, i, j = 0;

    float increment = range_increment(MIN_0, MAX_0, SCAN_TIME);
    tick = calcTicks(MIN_0, HERTZ);
    pwmWrite(SERVO_0, tick);  // set servo to minimum

    for (i = MIN_0; i <= MAX_0;  i+=increment)
    {
        cout << "Panning ss. Position: %d/n";
        tick = calcTicks(i, HERTZ);
        pwmWrite(SERVO_0, tick);
        pwmWrite(SERVO_1, tick);
        pwmWrite(SERVO_2, tick);
        pwmWrite(SERVO_3, tick);
    }
            
    for (j = i; j >= MIN_0; j-= increment)
    {
        cout << "Panning backwards. Position: %d/n";
        tick = calcTicks(j, HERTZ);
        pwmWrite(SERVO_0, tick);
        pwmWrite(SERVO_1, tick);
        pwmWrite(SERVO_2, tick);
        pwmWrite(SERVO_3, tick);
    }

}
