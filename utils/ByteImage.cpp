//
// Created by user on 16.07.2021.
//
#include <iostream>
#include "ByteImage.h"

cv::Mat ByteImage::decodeImage(byte *img) {
    unsigned short h = (img[0] << 8u) + img[1];
    unsigned short w = (img[2] << 8u) + img[3];
    unsigned short c = (img[4] << 8u) + img[5];
    byte *data = img + 6;

    cv::Mat image = cv::Mat(h, w, CV_8UC(c), data).clone(); // make a copy
    return image;
}

byte *ByteImage::encodeImage(const cv::Mat &img) {
    unsigned short h = img.rows;
    unsigned short w = img.cols;
    unsigned short c = img.channels();
    unsigned const int size = h * w * c + 3 * 2; //6 bytes for encoding metadata
    byte *bytes = new byte [size];

    bytes[0] = (h >> 8u);
    bytes[1] = (h & 0xFFu);
    bytes[2] = (w >> 8u);
    bytes[3] = (w & 0xFFu);
    bytes[4] = (c >> 8u);
    bytes[5] = (c & 0xFFu);

    for(int i = 0; i < h * w * c; i ++){
        bytes[i + 6] = img.data[i];
    }

    return bytes;
}

unsigned short ByteImage::getDataSize(byte *bytes){

}