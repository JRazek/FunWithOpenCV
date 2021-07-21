#include <iostream>
#include <opencv2/opencv.hpp>
#include "Server/TCPServer.h"
#include <future>
#include "utils/ByteImage.h"
#include "transferUtils/TransferObjectData.h"
#include "Client/TCPClient.h"

int main() {

    cv::Mat img = cv::imread("resources/aPhoto.jpg");


    const char * addr = "127.0.0.1";
    const u_short port = 12321;


    TCPServer server(port, 8192);
    TCPClient client(addr, port);

    server.listen();

    std::future<int> accept = std::async(&TCPServer::accept, &server);
    while (client.connect() < 0){
        sleep(10);
    }
    if(accept.get() > 0){
        std::cout<<"ERROR";
        return -1;
    }

    byte *encodedImg = ByteImage::encodeImage(img);

    u_int64_t dataSize = ByteImage::getDataSize(encodedImg) + ByteImage::imageMetadataSize;

    std::vector<byte> data;
    data.insert(data.end(), encodedImg, encodedImg + dataSize);

    const u_short PACKETS_COUNT = 10;


    client.sendPacketsMetaData(PACKETS_COUNT);

    int statusMetadata = server.readPacketsMetadata();

    std::future<decltype(server.readPacket())> fut = std::async(&TCPServer::readPacket, &server);


    for(int i = 0; i < PACKETS_COUNT; i ++) {
        client.sendPacket(data);
    }

    auto res = fut.get();

    cv::Mat decodedImg = ByteImage::decodeImage(res.second.data());

    cv::imshow("img", decodedImg);

    cv::waitKey(10);

    client.connClose();
    delete [] encodedImg;
    return 0;
}
