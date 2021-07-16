//
// Created by user on 13.07.2021.
//
#include "TestingClass.h"
#include "../utils/ByteImage.h"
#include <opencv2/opencv.hpp>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <opencv2/core/mat.hpp>
#include <thread>


void TestingClass::cameraTesting() {
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

void TestingClass::imageDilation() {
    cv::Mat readImage = cv::imread("resources/aPhoto.jpg", 0);
    cv::imshow("photo", readImage);
    cv::Mat dilatedImage;
    //cv::dilate(readImage, dilatedImage);
   // delete image;
}
void TestingClass::longFunction() {
    std::cout<<"Running long function...";
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
}

void TestingClass::convolutionWithMyKernel(cv::Mat &img){
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
int TestingClass::socketTestingClient(const cv::Mat &img, const int port, const char *addr){
    this->socketReady = true;
    if(!this->socketReady)
        return -1;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    //std::string message = "hello, idk pls work or sth";
    //const short port = 2000;

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
    byte * bytes = ByteImage::encodeImage(img);

    send(sock, bytes, ByteImage::getDataSize(bytes), 0);

    close(sock);

    delete [] bytes;
    return 0;
}

int TestingClass::socketTestingServer(const cv::Mat &mat, const int port){
    this->socketReady = false;
    int server_fd, new_socket, valread;
    struct sockaddr_in address{};
    int opt = 1;
    int addrlen = sizeof(address);
    const short BUFFER_SIZE = 8192;
    byte buffer[BUFFER_SIZE] = {0};
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        return -1;
    }

    // Forcefully attaching socket to the port 8080
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

    while(int size = read( new_socket, buffer, BUFFER_SIZE) > 0) {
        for(unsigned char & i : buffer) {
            bytesVector.push_back(i);
        }
    }

    byte * bytes = new byte [bytesVector.size()];
    for(int i = 0; i < bytesVector.size(); i ++){
        bytes[i] = bytesVector[i];
    }

    cv::Mat img = ByteImage::decodeImage(bytes);
    cv::imshow("img", img);
    cv::waitKey(5000);

    delete [] bytes;
    return 0;
}

