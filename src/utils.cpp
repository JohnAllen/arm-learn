#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include "../../raspicam/src/raspicam_still.h"

using namespace boost::filesystem;
using namespace std;

int getMaxFileNum(std::string dir)
{
    int max_int, file_num = 0;
    path p = "../training-images/*.jpg";
    directory_iterator it{p};
    while (it != directory_iterator{})
    {
        cout << *it++ << '\n';
    }
    return max_int;
}

int appendImageToFile(std::string file_name)
{             
    ofstream image_num_file;
    image_num_file.open("../images/training_images.txt", std::ios_base::app);
    image_num_file << file_name;
    return 0;
}

int captureImage(std::string file_name)
{
    raspicam::RaspiCam_Still Camera;

    sleep(1);
    cout << "opening camera capturing an image" << endl;
    Camera.setWidth(1280);
    Camera.setHeight(960);
    Camera.setISO(550);
    Camera.setBrightness(55);
    Camera.setEncoding(raspicam::RASPICAM_ENCODING_JPEG);
    Camera.open();

    sleep(1);
    unsigned int length = Camera.getImageBufferSize(); // Header + Image Data + Padding
    unsigned char * data = new unsigned char[length];

    if (!Camera.grab_retrieve(data, length)) {
        cerr<<"Error in grab"<<endl;
        return -1;
    }
    return 0;
}

