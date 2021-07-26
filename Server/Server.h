//
// Created by user on 25.07.2021.
//

#ifndef OPENCV_SERVER_H
#define OPENCV_SERVER_H

#include <opencv2/core/mat.hpp>
#include <queue>
#include "Server/TCPServer.h"

class Server : public TCPServer{
    std::queue<cv::Mat *> bufferedImages;
    virtual void notifyNewPacket(int socketID, std::vector<byte> &data);

public:
    void startShowingBufferedImages(int delay);
    Server();
    ~Server();
};


#endif //OPENCV_SERVER_H
