#include <iostream>
#include <opencv2/opencv.hpp>
#include "Server/TCPServer.h"
#include <future>
#include "utils/ByteImage.h"
#include "transferUtils/TransferObjectData.h"
#include "Client/TCPClient.h"

int main() {
    TCPServer server;
    server.addListener(12321, 16384);
    std::thread * serverThread = server.run();

    serverThread->join();


//
//    server.listen();
//
//    byte *encodedImg = ByteImage::encodeImage(img);
//
//    u_int64_t dataSize = ByteImage::getDataSize(encodedImg) + ByteImage::imageMetadataSize;
//
//    std::vector<byte> data;
//    data.insert(data.end(), encodedImg, encodedImg + dataSize);
//
//
//
//    cv::waitKey(10);
//
//    client.connClose();
//    delete [] encodedImg;
    return 0;
}
