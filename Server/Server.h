//
// Created by user on 25.07.2021.
//

#ifndef OPENCV_SERVER_H
#define OPENCV_SERVER_H

#include <opencv2/core/mat.hpp>
#include <queue>
#include "Server/TCPServer.h"
#include <unordered_set>

class Server : public TCPServer{
    std::unordered_map<int, std::queue<cv::Mat *>> bufferedImages; //socketID, queue of buffered images
    void notifyNewPacket(int socketID, std::vector<byte> &data) override;
    void notifySocketDone(int socketID) override;

public:
    void startShowingBufferedImages(int socketID, int delay);
    Server();
    ~Server();
};


#endif //OPENCV_SERVER_H
