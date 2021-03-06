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
#include <stdio.h>
#include "../../raspicam/src/raspicam_still.h"
#include "servo.h"
#include "utils.h"
#include "learn.h"

using namespace std;
const int TASK_TIME_LIMIT_SECS = 20;

int main ()
{

    cout << "BEGINNING TRAINING" << endl;

    int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
    if (fd < 0) {
        printf("Error in setup\n");
        return fd;
    }
    
    pca9685PWMReset(fd);
    int tick, i, j = 0;

    // start servos at some base position every time

    tick = calcTicks(i, HERTZ);
    resetServos();
  
    int TASK_ATTEMPT_DURATION_SECS; 
    bool SUCCESSFUL = false; 
    while (1==1) 
    {

        int CIRCUIT_CONNECTED = digitalRead(4);
        if (CIRCUIT_CONNECTED > 0/*pin is high*/)
        {
            SUCCESSFUL = true; // exit loop that will store servo times 
            resetServos(); // reset servo positions to base
            // write results to file
        }

        time_t now = time(NULL);
        time_t begin = time(NULL);
        TASK_ATTEMPT_DURATION_SECS = difftime(now, begin);
        cout << "SECONDS PASSED: " << TASK_ATTEMPT_DURATION_SECS << endl;
        cout << "I have " << TASK_TIME_LIMIT_SECS - TASK_ATTEMPT_DURATION_SECS << " seconds left to complete the task"<< endl;
        sleep(1);
   } 
   return 0;   
}
