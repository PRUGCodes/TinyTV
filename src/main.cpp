#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdint>
#include <string>
#include <chrono>
#include "../include/serialComm.hpp"

using namespace cv;

// serial speed -> 115,000

VideoCapture* getUserFile()
{
    std::string filepath{};
    std::cout << "Video file to display (filepath) --> ";
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

const std::string getUserPort() 
{
    std::string port{};
    std::cout << "Port to access (e.g. COM4) --> ";
    std::cin >> port;
    port = "\\\\.\\" + port;
    return port;
}

const std::string findAvg(int sum, int total) 
{
    std::string avg = std::to_string((sum / total));
    assert(avg.size() <= 3); // "COLOR VALUE GREATER THAN 3?? BUT HOW???"
    if (avg.size() == 2) 
    {
        avg = "0" + avg;
    }
    if (avg.size() == 1) 
    {
        avg = "00" + avg;
    }
    return avg;
}






int main(int argc, char *argv[])
{
    VideoCapture* cap = getUserFile();
    const std::uint16_t width = static_cast<int>(cap->get(CAP_PROP_FRAME_WIDTH));
    const std::uint16_t height = static_cast<int>(cap->get(CAP_PROP_FRAME_HEIGHT));
    const std::uint32_t total = width*height;
    const std::uint64_t totalFrames = static_cast<int>(cap->get(CAP_PROP_FRAME_COUNT));

    SerialPort* outputPort = new SerialPort(getUserPort().c_str());
    
    int fps = static_cast<int>(cap->get(CAP_PROP_FPS));
    std::cout << "FPS: " << fps << std::endl;
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;

    assert(outputPort->isConnected()); 



    int i = 0;
    // start video loop
    while (true) 
    {
        //auto startTime = std::chrono::high_resolution_clock::now();
        i++;
        Mat frame;
        if (!cap->read(frame))
        {
            std::cout << "Video end.\n";
            break;
        }

        std::uint32_t rsum = 0, gsum = 0, bsum = 0;

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
        std::cout << i << " / " << totalFrames << "\n";
        
        std::string avg{""};
        avg = avg + findAvg(bsum, total);
        avg = avg + findAvg(gsum, total);
        avg = avg + findAvg(rsum, total);

        
        std::cout << avg.c_str() << std::endl;
        
        if (!outputPort->writeSerialPort(avg.c_str(), sizeof(avg))) 
        {
            std::cerr << "ERROR! COULD NOT WRITE TO SERIAL PORT!!!! :(" << std::endl;
        };

        imshow("COW_WINDOW", frame);
        //auto endTime = std::chrono::high_resolution_clock::now();
        //int runTime = (endTime - startTime) / std::chrono::milliseconds(1);
        if(waitKey(1) == 27)
        {
            std::cout << "escape key pressed! exiting.\n";
            break;
        }
    }
    return 0;
}