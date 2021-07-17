//
// Created by user on 13.07.2021.
//

#ifndef OPENCV_TCPCONTROLLER_H
#define OPENCV_TCPCONTROLLER_H

#include <opencv2/opencv.hpp>
typedef unsigned char byte;

class TCPController {
    bool socketReady = false;
public:
    static void cameraTesting();
    static void imageDilation();
    static void longFunction();
    static void convolutionWithMyKernel(cv::Mat &);

    int socketTestingClient(const cv::Mat &mat, int port, const char *addr);
    int socketTestingServer(int port);
};


#endif //OPENCV_TCPCONTROLLER_H
