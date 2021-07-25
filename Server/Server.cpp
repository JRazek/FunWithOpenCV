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
    cv::Mat img = ByteImage::decodeImage(data.data());
    //todo some buffer to store images and once a second show them all in some specific order
}
