#include <opencv2/opencv.hpp>
#include "Server/TCPServer.h"
#include <thread>

int main() {
    TCPServer server;
    server.addListener(12321, 16384);
    std::thread * serverThread = server.run();

    serverThread->join();
    return 0;
}
