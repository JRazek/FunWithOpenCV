//
// Created by user on 13.07.2021.
//
#include "TCPController.h"
#include "../utils/ByteImage.h"
#include "../TCP/transferUtils/TransferObjectData.h"
#include <opencv2/opencv.hpp>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <opencv2/core/mat.hpp>
#include <thread>


void TCPController::cameraTesting() {
    cv::Mat image = cv::Mat();
    cv::VideoCapture videoCapture = cv::VideoCapture(0);

    cv::Mat edgedImage = cv::Mat();

    while (videoCapture.isOpened()) {
        videoCapture >> image;
        cv::GaussianBlur(image, image, cv::Size(7, 7), 10,10 );
        cv::Canny(image, edgedImage, 40,40 );
        cv::imshow("Window", edgedImage);
        cv::waitKey(1);
    }
}

void TCPController::imageDilation() {
    cv::Mat readImage = cv::imread("resources/aPhoto.jpg", 0);
    cv::imshow("photo", readImage);
    cv::Mat dilatedImage;
    //cv::dilate(readImage, dilatedImage);
   // delete image;
}
void TCPController::longFunction() {
    std::cout<<"Running long function...";
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
}

void TCPController::convolutionWithMyKernel(cv::Mat &img){
    cv::Mat buffer;
    const short kernelDepth = 1;
    const short kernelSize = 3;
    

    static signed short kernelStructure [kernelDepth][kernelSize][kernelSize] = 
    {
        {
             {0, 0, 0},
             {0, -1, 0},
             {0, 0, 0},

            // {-1, -1, -1},
            // {-1,  8, -1},
            // {-1, -1, -1},
        },
    };

}
int TCPController::socketTestingClient(const cv::Mat &img, const int port, const char *addr){
    if(!this->socketReady)
        return -1;
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if(inet_pton(AF_INET, addr, &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }


    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        printf("\nConnection Failed \n");
        return -1;
    }
    byte *bytes = ByteImage::encodeImage(img);
    unsigned int dataSize = ByteImage::getDataSize(bytes);

    byte *dataFormatted = TransferObjectData::encode(bytes, dataSize);
    u_int64_t formattedDataSize = TransferObjectData::decodeDataLength(dataFormatted);

    send(sock, dataFormatted, formattedDataSize, 0);

    close(sock);
    delete [] dataFormatted;
    delete [] bytes;
    return 0;
}

int TCPController::socketTestingServer(const int port){
    this->socketReady = false;
    int server_fd, new_socket;
    struct sockaddr_in address{};
    int opt = 1;
    int addrlen = sizeof(address);
    const short BUFFER_SIZE = 8192;
    byte buffer[BUFFER_SIZE] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        return -1;
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt))){
        perror("setsockopt");
        return -1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( port );

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){
        perror("bind failed");
        return -1;
    }
    if (listen(server_fd, 3) < 0){
        perror("listen");
        return -1;
    }
    this->socketReady = true;
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){
        perror("accept");
        return -1;
    }


    std::vector<byte> bytesVector;

    while(int packet = read( new_socket, buffer, BUFFER_SIZE)) {
        if(packet < 1)
            break;
        bytesVector.insert(bytesVector.end(), buffer, buffer + BUFFER_SIZE);
    }

    byte *test = new byte [bytesVector.size()];
    for(int i = 0; i < bytesVector.size(); i ++){
        test[i] = bytesVector[i];
    }

    cv::Mat img = ByteImage::decodeImage(bytesVector.data());
    cv::imshow("img", img);
    cv::waitKey(5000);

    return 0;
}

