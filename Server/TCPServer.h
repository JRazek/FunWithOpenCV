//
// Created by user on 17.07.2021.
//

#ifndef OPENCV_TCPSERVER_H
#define OPENCV_TCPSERVER_H

typedef unsigned short u_short;

class TCPServer {
    const u_short port;
public:
    TCPServer(u_short port);
};


#endif //OPENCV_TCPSERVER_H
