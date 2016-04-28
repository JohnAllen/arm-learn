#include <string>
#include <fstream>

using namespace std;
#ifndef UTILS 
#define UTILS 

#define IMG_WIDTH 1280
#define IMG_HEIGHT 960

int getMaxFileNum();
int appendImageToFile(std::string file_name);
int captureImage(std::string file_name);
int recordTaskCommands(time_t begin);

#endif
