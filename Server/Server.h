//
// Created by user on 25.07.2021.
//

#ifndef OPENCV_SERVER_H
#define OPENCV_SERVER_H

#include "Server/TCPServer.h"

class Server : TCPServer{
    virtual void notifyNewPacket(int socketID, std::vector<byte> &data);
};


#endif //OPENCV_SERVER_H
