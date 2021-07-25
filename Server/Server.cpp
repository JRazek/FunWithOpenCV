//
// Created by user on 25.07.2021.
//

#include "Server.h"
#include <opencv2/opencv.hpp>
#include "../utils/ByteImage.h"

void Server::notifyNewPacket(int socketID, std::vector<byte> &data) {
    //TCPServer::notifyNewPacket(socketID, data);
    cv::Mat img = ByteImage::decodeImage(data.data());
    cv::imshow("image", img);
    cv::waitKey(10000);
}
