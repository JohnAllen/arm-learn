#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <dirent.h>
#include <wiringPi.h>
#include <pca9685.h>
#include <fstream>
#include <ctime>
#include <string>
#include <chrono>
#include "servo.h"
#include <stdio.h>
#include "../../raspicam/src/raspicam_still.h"

using namespace std;

int main ()
{
    // required by ncurses.h; inits key read

    cout << "beginning" << endl;    
    int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
    if (fd < 0) {
        printf("Error in setup\n");
        return fd;
    }
    
    pca9685PWMReset(fd);
    int tick, i, j = 0;

    resetServos();
    // start servos at some base position every time
    tick = calcTicks(.6, HERTZ);
    pwmWrite(SERVO_0, tick);
    sleep(1);
    tick = calcTicks(2.4, HERTZ);
    pwmWrite(SERVO_0, tick);
    tick = calcTicks(.6, HERTZ);
    pwmWrite(SERVO_1, tick);
    tick = calcTicks(.6, HERTZ);
    pwmWrite(SERVO_1, tick);
    tick = calcTicks(.6, HERTZ);
    pwmWrite(SERVO_2, tick);
   }
 
