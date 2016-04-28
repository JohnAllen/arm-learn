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

    cout << "BEGINNING TEST" << endl;    
    int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
    if (fd < 0) {
        printf("Error in setup\n");
        return fd;
    }
    
    pca9685PWMReset(fd);
    int tick, i, j = 0;

/*    servoAngle(SERVO_0, 20);
    sleep(1);
    servoAngle(SERVO_0, 70);
    sleep(1);
    servoAngle(SERVO_0, 110);
*/
        /*resetServos();
    // start servos at some base position every time
    tick = calcTicks(.6, HERTZ);
    pwmWrite(SERVO_0, tick);
    sleep(1);
   */
}
 
