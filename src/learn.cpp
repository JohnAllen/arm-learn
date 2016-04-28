#include <ncurses.h>
#include <wiringPi.h>
#include <pca9685.h>
#include "servo.h"
#include "learn.h"
#include <fstream>
#include <iostream>
#include <time.h>
#include <unistd.h>

using namespace std;
const int TASK_TIME_LIMIT_SECS = 20;
int TASK_ATTEMPT_DURATION_SECS = 0;

int recordTaskCommands(time_t begin, int fd)  
{
    
 
    bool SUCCESSFUL = false; // has arm successfully completed its task?  
    cout << "Beginning attempt of robotic task.  I have " << TASK_TIME_LIMIT_SECS << " seconds to complete it" << endl;
            
    int key = getch();
    while (!SUCCESSFUL && TASK_ATTEMPT_DURATION_SECS < TASK_TIME_LIMIT_SECS)
    {

        // init ints that will hold keypress time for each servo button.  These numbers will ultimately fed to TensorFlow
        int h,i,j,k = 0;
        // if key pressed is one of our desired servo keys... http://www.asciitable.com/
        nodelay(stdscr, TRUE);  // make the screen input non-blocking
        while (key && key <= 107 && key >= 104)
        {
            cout << key << " pressed" << endl;
            // Record buttons for time depressed
            // Each loop increments key counter one second - see sleep(1) below 
                    
            // increase position of servo while its key is pressed
            switch (key)
            {
                case 104:
                {
                //        increaseServo(300);
                    h++;
                    cout << " h pressed" << endl;
                }
                case 105:
                {
                //      increaseServo(301);
                    i++;
                    cout << " i pressed" << endl;
                }
                case 106:
                {
                //    increaseServo(302);
                    j++;
                    cout << " j pressed" << endl;
                }
                case 107:
                {
                //   increaseServo(303);
                    k++;
                    cout << " k pressed" << endl;
                        }
                    }
                }

                // If electronic circuit has been completed
              int CIRCUIT_CONNECTED = digitalRead(4);
              if (1==2/*pin is high*/)
                {
                    SUCCESSFUL = true; // exit loop that will store servo times 
                    pca9685PWMReset(fd); // do we need this?
                    resetServos(); // reset servo positions to base
                }

                time_t now = time(NULL);
                TASK_ATTEMPT_DURATION_SECS = difftime(now, begin);
                cout << "SECONDS PASSED: " << TASK_ATTEMPT_DURATION_SECS << endl;
                cout << "I have " << TASK_TIME_LIMIT_SECS - TASK_ATTEMPT_DURATION_SECS << " seconds left to complete the task"<< endl;
                sleep(1);
               }   
}

int writeResults()
{

}
