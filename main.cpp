#include <iostream>
#include <thread>
#include <opencv2/opencv.hpp>
#include "Tests/TestingClass.h"

int main() {
    
    cv::Mat img = cv::imread("resources/aPhoto.jpg");

    char * addr = "127.0.0.1";
    TestingClass::socketTesting(img, 2000, addr);
    return 0;
}
