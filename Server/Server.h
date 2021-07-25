//
// Created by user on 25.07.2021.
//

#ifndef OPENCV_SERVER_H
#define OPENCV_SERVER_H

#include <opencv2/core/mat.hpp>
#include "Server/TCPServer.h"

class Server : public TCPServer{
    std::vector<cv::Mat *> bufferedImages;
    virtual void notifyNewPacket(int socketID, std::vector<byte> &data);

    //should be run every second to show all the images. Also calculate the right delay and sizes to operate.
    void showBufferedImagesAndClearBuffer();
    ~Server();
};


#endif //OPENCV_SERVER_H
