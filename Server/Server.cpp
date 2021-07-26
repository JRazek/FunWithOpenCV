//
// Created by user on 25.07.2021.
//

#include "Server.h"
#include <opencv2/opencv.hpp>
#include "../utils/ByteImage.h"
#include "Logger/Logger.h"
void Server::notifyNewPacket(int socketID, std::vector<byte> &data) {
    //TCPServer::notifyNewPacket(socketID, data);
    Logger::log("new packet", LEVEL::DEBUG);
    auto * img = new cv::Mat(ByteImage::decodeImage(data.data()));
    bool newWindow = this->bufferedImages.find(socketID) == bufferedImages.end();
    if(newWindow){
        this->bufferedImages[socketID] = std::queue<cv::Mat *>();
    }
    this->bufferedImages[socketID].emplace(img);
    if(newWindow){
        this->startShowingBufferedImages(socketID, 16);
    }
}

Server::~Server() {
    for(auto k : bufferedImages){
        while(!k.second.empty()){
            cv::Mat * bufferedImage = k.second.front();
            k.second.pop();
            delete bufferedImage;
        }
    }
}

void Server::startShowingBufferedImages(int socketID, int delay) {
    std::thread videoThread([this, delay, socketID]{
        auto &queue = bufferedImages[socketID];
        while(!queue.empty()){
            cv::Mat *video = queue.front();
            queue.pop();
            cv::imshow("webCam" + std::to_string(socketID), *video);
            cv::waitKey(delay);
            delete video;
        }
        this->bufferedImages.erase(socketID);
    });
    videoThread.detach();
}

void Server::notifySocketDone(int socketID) {
    TCPServer::notifySocketDone(socketID);
    cv::destroyWindow("webCam" + std::to_string(socketID));
}

Server::Server() = default;
