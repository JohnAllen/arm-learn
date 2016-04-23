#include <stdio.h>
#include <raspicam/raspicam.h>
#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <wiringPi.h>
#include <fstream>
/*
 *  Teach an arm to learn to move to a certain location given an image containing that location
 *
 *  There is the question of specifying the location of the object in pixels or just giving it an image and hoping it doe 
 *  its thing with a given image.
 *  I want to use an electronic success signal: when the end-effector reaches the desired location, a circuit is complete
 *  I like this approach because it is very binary and obvious whether or not the task has been successfully accomplished.
 *  The computer will know on its own whether or not it has been successful.  
 *  Idea is to manually move the end-effector with buttons a few times for a given image - perhaps only one time for each
 *  position, and see how well it does.
 */

using namespace std;
const int TASK_TIME_LIMIT_SECS = 20;

int main ()
{
    // required by ncurses.h; inits key read
    initscr();
    // initiate/instantiate Raspicam
    raspicam::RaspiCam Camera;
    
    while (1==1) 
    {
        int key = getch();  // read keyboard input
        cout << key << endl;
        
        if (key == ' ' || key == 32) // TODO which one? 
        {
            // Capture an image
            // Save it to a file to be read into TensorFlow later 

            cout << "Opening Camera..." << endl;
            if (!Camera.open())
            {
                cerr<<"Error opening camera"<<endl;
                return -1;
            }
            cout << "capturing an image" << endl; 
            Camera.grab();
    
            unsigned char *data=new unsigned char[Camera.getImageTypeSize (raspicam::RASPICAM_FORMAT_GRAY )];
            Camera.retrieve(data,raspicam::RASPICAM_FORMAT_GRAY);  //get the image
    //save
            // TODO what to name files?
            std::ofstream outFile("TODO.ppm",std::ios::binary);
            outFile<<"P6\n"<<Camera.getWidth() <<" "<<Camera.getHeight() << endl;
            outFile.write(( char* ) data, Camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_GRAY));
            
            cout<<"Image saved at raspicam_image.ppm"<<endl;
            // delete the image from memory
            delete data; 

            // wait one second to allow image to be written to file before recording servo inputs
            sleep(1);
    
            bool SUCCESSFUL = false; // has arm successfully completed its task?
            
            // Begin recording button movements to complete move task
            // time to complete task counter; 
            //  if time greater than some max amount, don't even include it in our dataset - start over.  
            //  This could go on for ours if exploring to much or something else goes wrong.
            int TASK_ATTEMPT_DURATION_SECS = 0;
            time_t begin = time(NULL); 
            while (!SUCCESSFUL && TASK_ATTEMPT_DURATION_SECS < TASK_TIME_LIMIT_SECS)
            {
                cout << "Beginning attempt of robotic task.  I have " << TASK_TIME_LIMIT_SECS << " seconds to complete it" << endl;
                // init ints that will hold keypress time for each servo button.  These numbers will ultimately fed to TensorFlow
                int h,i,j,k = 0;
                // if key pressed is one of our desired servo keys... http://www.asciitable.com/
                nodelay(stdscr, TRUE);  // make the screen input non-blocking
                while (key && key <= 107 && key >= 104) 
                {
                    cout << key << " pressed" << endl;
                    // Record buttons for time depressed
                    // Each loop increments key counter one second - see sleep(1) below 
                    switch (key)
                    {
                        case 104:
                        {
                            h++;
                            cout << " h pressed" << endl;
                        }
                        case 105:
                        {
                            i++;
                            cout << " i pressed" << endl;
                        }
                        case 106:
                        {
                            j++;
                            cout << " j pressed" << endl;
                        }
                        case 107:
                        {
                            k++;
                            cout << " k pressed" << endl;
                        }
                    }                    
                }

                // If electronic circuit has been completed
                if (1==2/*pin is high*/)
                {
                    SUCCESSFUL = true; // exit loop that will store servo times 
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
