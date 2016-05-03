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
#include <unistd.h>
#include <iostream>

using namespace std;

int main ()
{

    cout << "BEGINNING TEST" << endl;    
    int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
    if (fd < 0) {
        printf("Error in setup\n");
        return fd;
    }

//    pinMode(4, INPUT);    
    pca9685PWMReset(fd);
    int tick, i, j = 0;

    resetServos();

    posArm(100);
/*    servoAngle(SERVO_1, HRZ_1);
    sleep(.5);
    servoAngle(SERVO_2, HRZ_2);
    sleep(.5);
/*    servoAngle(SERVO_0, MID_0);
    sleep(.5);

    servoAngle(SERVO_2, UP_2);
    sleep(.5);

    servoAngle(SERVO_2, UP_1);
*/
    int success = digitalRead(4);
    if (success > 0)
        cout << "SUCCESS!!!" << endl;    

}
 
