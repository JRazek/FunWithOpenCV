//
// Created by user on 17.07.2021.
//

#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdio>
#include <zconf.h>
#include "TCPServer.h"

TCPServer::TCPServer(u_short port, u_short BUFFER_SIZE):port(port), BUFFER_SIZE(BUFFER_SIZE) {
    this->socketReady = false;
    int opt = 1;

    if ((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        this->constructorError = 301;
        return;
    }


    if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt))){
        perror("setsockopt");
        this->constructorError = 302;
        return;
    }
    this->address.sin_family = AF_INET;
    this->address.sin_addr.s_addr = INADDR_ANY;
    this->address.sin_port = htons( port );

    if (bind(this->server_fd, (struct sockaddr *)&this->address, sizeof(this->address))<0){
        perror("bind failed");
        this->constructorError = 303;
        return;
    }
}

u_short TCPServer::listen() {
    int addrLen = sizeof(address);
    if (::listen(server_fd, 3) < 0){
        perror("listen");
        return -1;
    }
    this->socketReady = true;
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrLen))<0){
        perror("accept");
        return -1;
    }
    return 0;
}

std::pair<u_short, std::vector<byte>> TCPServer::readPacket() {
    byte buffer[this->BUFFER_SIZE];
    std::vector<byte> bytesVector;
    u_int64_t dataSize;
    bool dataNow = false;

    u_short dataRequestedSize = BUFFER_SIZE;

    byte packetData[8];

    int status = read(new_socket, packetData, sizeof(packetData));
    if(status < 0)
        return {-1, {}};



    return std::pair<u_short, std::vector<byte>>();
}
