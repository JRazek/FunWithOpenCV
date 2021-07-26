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
    cv::Mat * img = new cv::Mat(ByteImage::decodeImage(data.data()));
    this->bufferedImages.push_back(img);
    //todo some buffer to store images and once a second show them all in some specific order
}

Server::~Server() {
    for(auto i : bufferedImages) {
        delete i;
    }
}

void Server::showBufferedImagesAndClearBuffer() {
    for(auto b : bufferedImages){
        cv::imshow("image", *b);
        cv::waitKey(1);
        delete b;
    }
    this->bufferedImages.clear();
}

Server::Server() = default;
