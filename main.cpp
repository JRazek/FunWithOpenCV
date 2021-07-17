#include <iostream>
#include <thread>
#include <opencv2/opencv.hpp>
#include "Tests/TCPController.h"
#include "TCP/Server/TCPServer.h"
#include <future>
#include "utils/ByteImage.h"
#include "TCP/transferUtils/TransferObjectData.h"
#include "TCP/Client/TCPClient.h"

int main() {

    cv::Mat img = cv::imread("resources/aPhoto.jpg");

    TCPController testingClass;

    const char * addr = "127.0.0.1";
    const u_short port = 12321;


    TCPServer server(port, 8192);
    TCPClient client(addr, port);

    server.listen();

    std::future<u_short> accept = std::async(&TCPServer::accept, &server);
    while (client.connect() < 0){
        sleep(10);
    }

    std::vector<byte> data = {'d','e','b','i','l','9'};

    if(client.sendData(data) > 0){
        std::cout<<"ERROR";
        return -1;
    }
    if(accept.get() > 0){
        std::cout<<"ERROR";
        return -1;
    }


    std::future<std::pair<u_short , std::vector<byte>>> fut = std::async(&TCPServer::readPacket, &server);
    std::pair<u_short , std::vector<byte>> res = fut.get();
    for(int i = 0 ; i < res.second.size(); i ++){
        std::cout<<res.second[i]<<" ";
    }

    return 0;
}
