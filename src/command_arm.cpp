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
#include "utils.h"
#include "learn.h"
#include <stdio.h>
#include "../../raspicam/src/raspicam_still.h"

using namespace std;
const int TASK_TIME_LIMIT_SECS = 20;

int main ()
{

    cout << "INITIATING SETUP" << endl;

    int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
    if (fd < 0) {
        printf("Error in setup\n");
        return fd;
    }
    
    pca9685PWMReset(fd);
    int tick, i, j = 0;

    // start servos at some base position every time

    tick = calcTicks(i, HERTZ);
    pwmWrite(SERVO_0, tick);
    
//    resetServos();

    initscr();
    while (1==1) 
    {
        int key = getch();  // read keyboard input
        cout << "key" << key << "pressed" << endl;
        
        if (key == ' ' || key == 32) 
        {
            time_t begin = time(NULL);
            recordTaskCommands(begin, fd);

        }
    sleep(.5);
   } 
                return 0;   
}
