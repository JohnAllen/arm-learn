#include <stdio.h>
//#include <raspicam/raspicam.h>
#include <iostream>
/*
 * Teach an arm to learn to move to a certain location given an image containing that location
 *
 *  There is the question of specifying the location of the object in pixels or just giving it an image and hoping it doe 
 *  its thing with a given image.
 *  
 *  I want to use an electronic success signal: when the end-effector reaches the desired location, a circuit is complete
 *  
 *  I like this approach because it is very binary and obvious whether or not the task has been successfully accomplished.
 *  The computer will know on its own whether or not it has been successful.  
 *
 *  Idea is to manually move the end-effector with buttons a few times for a given image - perhaps only one time for each
 *  position, and see how well it does.
 */

using namespace std;

int main ()
{
    //raspicam::RaspiCam Camera;
    while (1==1) 
    {
     /*   cout << "Opening Camera..." << endl;
         if (!Camera.open())
         {
             cerr<<"Error opening camera"<<endl;
             return -1;
         }
         Camera.grab();
    */
        // Capture an image
        // Save it to a file to be read into a TF Python interface later 
        if (getchar() == 32)
        {
            bool SUCCESSFUL = false;
            // Begin recording button movements to complete move task
            while (!SUCCESSFUL)
            {
                // if key pressed is one of our desired servo keys... http://www.asciitable.com/
                int key = getchar();
                if (key == 104 || key == 105 || key == 106 || key == 107)
                {
                    cout << key << endl;
                    // Record buttons for time depressed
                }
                if (1==2/*pin is high*/)
                {
                    SUCCESSFUL = true;
                }
            }
            // reset servo to initial state and wait for another 32/space bar
            // ...      
        }
   } 
                return 0;   
}
