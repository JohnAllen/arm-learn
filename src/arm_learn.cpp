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
#include "servo_commands.h"
#include <stdio.h>
#include "../../raspicam/src/raspicam_still.h"

using namespace std;
const int TASK_TIME_LIMIT_SECS = 20;

int main ()
{
    // required by ncurses.h; inits key read
    int TASK_ATTEMPT_DURATION_SECS = 0;
    
    int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
    
    if (fd < 0) {
        printf("Error in setup\n");
        return fd;
    }
    
    pca9685PWMReset(fd);
    int tick, i, j = 0;

    // start servos at some base position every time
    resetServos();

    initscr();
    while (1==1) 
    {
        int key = getch();  // read keyboard input
        cout << "key" << key << "pressed" << endl;
        
        if (key == ' ' || key == 32 || TASK_ATTEMPT_DURATION_SECS >= TASK_TIME_LIMIT_SECS) // TODO which one? 
        {
            // Capture an image
            // Save it to a file to be read into TensorFlow later 
            // initiate/instantiate Raspicam
           raspicam::RaspiCam_Still Camera;
            cout << "Opening Camera..." << endl;
            sleep(1); 
            cout << "opening camera capturing an image" << endl; 
            Camera.setWidth(1280);
            Camera.setHeight(960);
            Camera.setISO(600);
            Camera.setBrightness(65);
            Camera.setEncoding(raspicam::RASPICAM_ENCODING_JPEG); 
            Camera.open();

            sleep(1);
            
            unsigned int length = Camera.getImageBufferSize(); // Header + Image Data + Padding
            unsigned char * data = new unsigned char[length];
            if ( !Camera.grab_retrieve(data, length) ) {
                cerr<<"Error in grab"<<endl;
                return -1;
            }

            cout << "saving picture.jpg" << endl;
            ofstream file ( "picture.jpg",ios::binary );
            file.write(( char*)data, length);

            delete data; 

            bool SUCCESSFUL = false; // has arm successfully completed its task?
            
            // time to complete task counter; 
            //  if time greater than some max amount, don't even include it in our dataset - start over.  
            //  This could go on for ours if exploring to much or something else goes wrong.
            time_t begin = time(NULL); 
            cout << "Beginning attempt of robotic task.  I have " << TASK_TIME_LIMIT_SECS << " seconds to complete it" << endl;
            
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
                            increaseServo(300);
                            h++;
                            cout << " h pressed" << endl;
                        }
                        case 105:
                        {
                            increaseServo(301);
                            i++;
                            cout << " i pressed" << endl;
                        }
                        case 106:
                        {
                            increaseServo(302);
                            j++;
                            cout << " j pressed" << endl;
                        }
                        case 107:
                        {
                            increaseServo(303);
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
            // write individual servo times somewhere once task was successful
            // reset servo to initial state and wait for another 32/space bar
        }
    sleep(.5);
   } 
                return 0;   
}
