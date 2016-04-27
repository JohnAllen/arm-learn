#include "servo_commands.h"
#include <iostream>
#include <wiringPi.h>
#include <pca9685.h>

/**
 *  *  *  * Calculate the number of ticks the signal should be high for the required amount of time
 *   *   *   */

int PIN_NUMS[4] = {SERVO_0, SERVO_1, SERVO_2, SERVO_3};

using namespace std;

int calcTicks(float impulseMs, int hertz)
{
    float cycleMs = 1000.0f / hertz;
    return (int)(MAX_PWM * impulseMs / cycleMs + 0.5f);
}

float map(float input, float min, float max)
{
    return (input * max) + (1 - input) * min;
}

float range_increment(float min, float max, float millis)
{
    return (max - min) / millis;
}

int angleMicroSec(int tick)
{
    return tick;
}

int resetServos()
{
    int i;
    for (i = 0; i < sizeof(PIN_NUMS); i++)
    {
        cout << "turning off servo with pin: " << PIN_NUMS[i] << endl;
        setServoMin(PIN_NUMS[i]);
    }
}

int setServoMin(int num)
{
    int tick = calcTicks(.6, HERTZ);
    pwmWrite(num, tick);
    return 0;
}

int getMaxFileNum()
{
    int max_int, file_num = 0;
    BOOST_FOREACH(const std::string& fname, ls( "../images/*.jpg"))
    {
        size_t lastindex = fname.find_last_of("."); 
        string rawname = fname.substr(0, lastindex); 
        cout << "file_num is " << rawname << endl;
        file_num = std::stoi(rawname);
        if (file_num > max_int)
        {
            max_int = file_num;
            cout << "max_int is now " << max_int << endl;
        }
        cout << "File number is " << file_num << endl;
    }

    return max_int;
}

void appendImageToFile(char file_name[12])
{
    ofstream image_num_file;
    image_num_file.open("../images/training_images.txt", std::ios_base::app);
    image_num_file << file_name;
}
