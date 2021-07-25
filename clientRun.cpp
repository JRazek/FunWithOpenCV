//
// Created by user on 25.07.2021.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "Client/TCPClient.h"
#include "utils/ByteImage.h"

int main() {
    const char *ip = "10.0.0.9";
    const u_short port = 12321;
    TCPClient tcpClient(ip, port);
    tcpClient.connect();
    cv::VideoCapture cam(0);
    cv::Mat video;
    cam.read(video);
    byte * data = ByteImage::encodeImage(video);

    tcpClient.sendPacket(data, ByteImage::getDataSize(data) + ByteImage::imageMetadataSize);

    cv::waitKey(10000);
    return 0;
}
