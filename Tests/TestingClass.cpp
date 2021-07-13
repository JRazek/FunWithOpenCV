//
// Created by user on 13.07.2021.
//
#include "TestingClass.h"
#include <opencv2/opencv.hpp>

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
    cv::Mat tmp = cv::imread("resources/aPhoto.jpg", 0);
    cv::imshow("photo", tmp);

   // delete image;
}