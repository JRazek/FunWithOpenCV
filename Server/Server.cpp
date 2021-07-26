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
    this->bufferedImages.emplace(img);
    //todo some buffer to store images and once a second show them all in some specific order
}

Server::~Server() {
    while(!bufferedImages.empty()){
        cv::Mat * bufferedImage = bufferedImages.front();
        bufferedImages.pop();
        delete bufferedImage;
    }
}

void Server::startShowingBufferedImages(int delay) {
    std::thread videoThread([this, delay]{
        while(true){
            if(!bufferedImages.empty()) {
                cv::Mat *video = bufferedImages.front();
                bufferedImages.pop();
                cv::imshow("web cam", *video);
                cv::waitKey(delay);
                delete video;
            }
        }
    });
    videoThread.detach();
}

Server::Server() = default;
