//
// Created by user on 13.07.2021.
//

#ifndef OPENCV_TESTINGCLASS_H
#define OPENCV_TESTINGCLASS_H

#include <opencv2/opencv.hpp>

class TestingClass {
public:
    static void cameraTesting();
    static void imageDilation();
    static void longFunction();
    static void convolutionWithMyKernel(cv::Mat &);
    static int socketTesting(const cv::Mat &mat, const int port, const char *addr);
};


#endif //OPENCV_TESTINGCLASS_H
