#include <iostream>
#include <thread>
#include <opencv2/opencv.hpp>
#include "Tests/TCPController.h"
#include "utils/ByteImage.h"

int main() {
    
    cv::Mat img = cv::imread("resources/aPhoto.jpg");

    TCPController testingClass;

    const char * addr = "127.0.0.1";
//    std::thread t1(&TCPController::socketTestingServer, &testingClass, 12321);
//    byte *bytes = ByteImage::encodeImage(img);
//    img = ByteImage::decodeImage(bytes);
//    cv::imshow("img", img);
//    cv::waitKey(5000);
//    while (testingClass.socketTestingClient(img, 12321, addr) != 0);
//
//    t1.join();




    return 0;
}
