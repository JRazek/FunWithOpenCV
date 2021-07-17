//
// Created by user on 17.07.2021.
//

#ifndef OPENCV_TCPSERVER_H
#define OPENCV_TCPSERVER_H
#include <vector>

typedef unsigned short u_short;
typedef unsigned char byte;

class TCPServer {
    const u_short port;
    bool socketReady;
    const u_short BUFFER_SIZE = 8192;
private:
    u_short constructorError;
    struct sockaddr_in address{};
    int server_fd, new_socket{};


public:
    TCPServer(u_short port, u_short BUFFER_SIZE);
    u_short listen();
    /**
     * start listening on specified port
     **/
    std::pair<u_short, std::vector<byte>> readPacket();
};


#endif //OPENCV_TCPSERVER_H
