#include <iostream>
#include <thread>
#include <opencv2/opencv.hpp>
#include "Tests/TestingClass.h"

int main() {
    
    cv::Mat img = cv::imread("resources/aPhoto.jpg");

    std::cerr << img.channels() << "\n";
    TestingClass::convolutionWithMyKernel(img);

   // TestingClass::cameraTesting();

    return 0;
}
