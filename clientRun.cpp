//
// Created by user on 25.07.2021.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include "Client/TCPClient.h"
#include "utils/ByteImage.h"

int main() {
    const char *ip = "10.0.0.9";
    const u_short port = 12321;
    TCPClient tcpClient(ip, port);
    if(tcpClient.connect() < 0)
        return -1;
    cv::VideoCapture cam(0);
    cv::Mat video;

    while(1) {
        const int packetCount = 1000;

        tcpClient.sendPacketsMetaData(packetCount);
        for (int i = 0; i < packetCount; i++) {
            cam.read(video);
            byte *data = ByteImage::encodeImage(video);
            if(tcpClient.sendPacket(data, ByteImage::getDataSize(data) + ByteImage::imageMetadataSize) < 0)
                return -1;
            cv::waitKey(16);
            delete data;
        }
    }
    return 0;
}
