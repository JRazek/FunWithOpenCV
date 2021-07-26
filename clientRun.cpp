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
    TCPClient tcpClient1(ip, port);
    if(tcpClient1.connect() < 0)
        return -1;
    TCPClient tcpClient2(ip, port);
    if(tcpClient2.connect() < 0)
        return -1;
    cv::VideoCapture cam(0);
    cv::Mat video;

    while(1) {
        const int packetCount = 1000;

        tcpClient1.sendPacketsMetaData(packetCount);
        tcpClient2.sendPacketsMetaData(packetCount);
        for (int i = 0; i < packetCount; i++) {
            cam.read(video);
            byte *data = ByteImage::encodeImage(video);
            if(tcpClient1.sendPacket(data, ByteImage::getDataSize(data) + ByteImage::imageMetadataSize) < 0)
                return -1;
            if(tcpClient2.sendPacket(data, ByteImage::getDataSize(data) + ByteImage::imageMetadataSize) < 0)
                return -1;
            cv::waitKey(16);
            delete data;
        }
    }
}
