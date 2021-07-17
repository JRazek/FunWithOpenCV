#include <iostream>
#include <thread>
#include <opencv2/opencv.hpp>
#include "Tests/TCPController.h"
#include "Server/TCPServer.h"
#include <future>
#include "utils/ByteImage.h"
#include "Server/transferUtils/TransferObjectData.h"

int test(int x){
    return x;
}
int main() {

    cv::Mat img = cv::imread("resources/aPhoto.jpg");

    TCPController testingClass;

    const char * addr = "127.0.0.1";
    const u_short port = 12321;

    TCPServer server(port, 8192);
    server.listen();

    std::future<std::pair<u_short , std::vector<byte>>> fut = std::async(&TCPServer::readPacket, &server);


   // delete [] encoded;
    //delete [] res.second;
    return 0;
}
