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
#include "utils.h"
#include "servo_commands.h"
#include <stdio.h>
#include "../../raspicam/src/raspicam_still.h"

using namespace std;
const int TASK_TIME_LIMIT_SECS = 20;

int main ()
{
    // required by ncurses.h; inits key read
    int TASK_ATTEMPT_DURATION_SECS = 0;

    cout << "SETTING UP" << endl;    
    int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
    if (fd < 0) {
        printf("Error in setup\n");
        return fd;
    }
    
    pca9685PWMReset(fd);
    int tick, i, j = 0;

    resetServos();
    
    initscr();
    while (1==1) 
    {
        int key = getch();  // read keyboard input
        cout << "key" << key << "pressed" << endl;
        
        if (key == ' ' || key == 32 || TASK_ATTEMPT_DURATION_SECS >= TASK_TIME_LIMIT_SECS) // TODO which one? 
        {

            // capture an image
            int highest_file_num = getMaxFileNum();
            std::string file_name = std::to_string(highest_file_num);
            
            file_name = file_name + ".jpg";
            cout << "saving training image with num " << file_name << endl;
            captureImage(highest_file_num);
            ofstream file (file_name, ios::binary);
            file.write(( char*)data, length);

            delete data; 

            appendImageToFile(file_name);
            time_t begin = time(NULL); 
            recordTaskCommands();
        }
    sleep(.25);
   } 
                return 0;   
}
