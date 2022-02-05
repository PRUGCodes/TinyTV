#include <opencv2/opencv.hpp>
#include <iostream>
#include <charconv>
#include <string>
//#include <cassert>
#include "../include/serialComm.hpp"

using namespace cv;
constexpr char* portName = "\\\\.\\COM20";

// serial speed -> 115,000

VideoCapture* getUserInput()
{
    std::string filepath{};
    std::cout << "Video file to display (filepath)--> ";
    std::cin >> filepath;
    VideoCapture* cap = new VideoCapture(filepath);
    if (!cap->isOpened())
    {
        std::cerr << "Could not open! :(\n";
        std::cin;
        return nullptr;
    }
    return cap;
}






int main(int argc, char *argv[])
{
    VideoCapture* cap = getUserInput();
    const int width = static_cast<int>(cap->get(CAP_PROP_FRAME_WIDTH));
    const int height = static_cast<int>(cap->get(CAP_PROP_FRAME_HEIGHT));
    const int totalFrames = static_cast<int>(cap->get(CAP_PROP_FRAME_COUNT));

    SerialPort* outputPort = new SerialPort(portName);
    //delete cap;
    
    int fps = static_cast<int>(cap->get(CAP_PROP_FPS));
    std::cout << "FPS: " << fps << std::endl;
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;

    assert(outputPort->isConnected(), "CONNECTION FAILED");



    int i = 0;
    // start video loop
    while (true) 
    {
        i++;
        Mat frame;
        if (!cap->read(frame))
        {
            std::cout << "Video end.\n";
            break;
        }

        unsigned long long rsum = 0, gsum = 0, bsum = 0;

        for (int x = 0; x<width; x++)
        {
            for (int y = 0; y<height; y++) 
            {
                Vec3b pixel = frame.at<Vec3b>(y, x);
                rsum += pixel[0];
                gsum += pixel[1];
                bsum += pixel[2];
            }
        }
        std::cout << " FRAMES: "<< i << " / " << totalFrames << "\r";
        const char* average = 
        
        outputPort->writeSerialPort(average, sizeof(average));
        //imshow("COW_WINDOW", frame);
        /*if(waitKey(1) == 27)
        {
            std::cout << "escape key pressed! exiting.\n";
            break;
        }*/
    }
    return 0;
}