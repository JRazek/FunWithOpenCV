#include <iostream>
#include <thread>
#include <opencv2/opencv.hpp>
#include "Tests/TestingClass.h"

int main() {
    
    cv::Mat img = cv::imread("resources/aPhoto.jpg");

    TestingClass testingClass;

    const char * addr = "127.0.0.1";

   // std::thread t1(&TestingClass::socketTestingServer, &testingClass, img, 12321);

    while (testingClass.socketTestingClient(img, 12321, addr) != 0);

    //t1.join();
    return 0;
}
