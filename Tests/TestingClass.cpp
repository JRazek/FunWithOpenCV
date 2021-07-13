//
// Created by user on 13.07.2021.
//
#include "TestingClass.h"
#include <opencv2/opencv.hpp>
#include <thread>

void TestingClass::cameraTesting() {
    cv::Mat image = cv::Mat();
    cv::VideoCapture videoCapture = cv::VideoCapture(0);

    cv::Mat edgedImage = cv::Mat();

    while (videoCapture.isOpened()) {
        videoCapture >> image;
        cv::GaussianBlur(image, image, cv::Size(7, 7), 10,10 );
        cv::Canny(image, edgedImage, 40,40 );
        cv::imshow("Window", edgedImage);
        cv::waitKey(1);
    }
}

void TestingClass::imageDilation() {
    cv::Mat readImage = cv::imread("resources/aPhoto.jpg", 0);
    cv::imshow("photo", readImage);
    cv::Mat dilatedImage;
    //cv::dilate(readImage, dilatedImage);
   // delete image;
}
void TestingClass::longFunction() {
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::cout<<"Running long function...";
}