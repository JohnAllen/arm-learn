#include <string>
#include <fstream>

using namespace std;
#ifndef UTILS 
#define UTILS 


int getMaxFileNum();
int appendImageToFile(std::string file_name);
int captureImage(std::string file_name);
int recordTaskCommands(time_t begin);

#endif
