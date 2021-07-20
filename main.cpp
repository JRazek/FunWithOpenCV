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

    std::future<u_short> accept = std::async(&TCPServer::accept, &server);
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

    //todo some condition
    for(int i = 0; i < 10; i ++) {
        std::future<std::pair<u_short, std::vector<byte>>> fut = std::async(&TCPServer::readPacket, &server);

        if (client.sendData(data) > 0) {
            std::cout << "ERROR";
            return -1;
        }

        std::pair<u_short, std::vector<byte>> res = fut.get();


        cv::Mat decodedImg = ByteImage::decodeImage(res.second.data());

        cv::imshow("img", decodedImg);

        cv::waitKey(10);
    }
    client.connClose();
    delete [] encodedImg;
    return 0;
}
