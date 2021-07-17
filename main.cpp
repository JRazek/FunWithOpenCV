#include <iostream>
#include <thread>
#include <opencv2/opencv.hpp>
#include "Tests/TCPController.h"
#include "Server/TCPServer.h"
#include "utils/ByteImage.h"
#include "Server/transferUtils/TransferObjectData.h"

int main() {
    
    cv::Mat img = cv::imread("resources/aPhoto.jpg");

    TCPController testingClass;

    const char * addr = "127.0.0.1";
//    std::thread t1(&TCPController::socketTestingServer, &testingClass, 12321);
//    byte *bytes = ByteImage::encodeImage(img);
//    img = ByteImage::decodeImage(bytes);
//    cv::imshow("img", img);
//    cv::waitKey(5000);
//    while (testingClass.socketTestingClient(img, 12321, addr) != 0);
//
//    t1.join();

//    TCPServer server(12321, 8192);
//    server.listen();
//    std::thread t1(&TCPServer::socketTestingServer, &testingClass, 12321);

    byte testBytes[] = "debil";
    byte * encoded = TransferObjectData::encode(testBytes, sizeof(testBytes));

    std::pair<u_int64_t, byte *> res = TransferObjectData::decode(encoded);

    for(int i = 0; i < res.first; i ++)
        std::cout<<res.second[i]<<" ";

    delete [] encoded;
    return 0;
}
