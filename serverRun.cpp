#include <opencv2/opencv.hpp>
#include "Server/Server.h"
#include <thread>

int main() {
    Server server;
    server.addListener(12321,10000);
    std::thread * serverThread = server.run();

    serverThread->join();
    return 0;
}
