#include <string>
#include <fstream>
#include "servo.h"
#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <wiringPi.h>
#include <pca9685.h>
#include <fstream>
#include <ctime>
#include <chrono>

#ifndef LEARN_H
#define LEARN_H 

int recordTaskCommands(time_t begin, int fd);

#endif
