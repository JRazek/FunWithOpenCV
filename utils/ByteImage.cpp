//
// Created by user on 16.07.2021.
//

#include "ByteImage.h"

cv::Mat ByteImage::decodeImage(byte *image) {

    return cv::Mat();
}

byte *ByteImage::encodeImage(const cv::Mat &img) {
    unsigned int h = img.rows;
    unsigned int w = img.cols;
    unsigned short c = img.channels();
    unsigned const int size = h * w * c + 3 * 4;
    byte *bytes = new byte [size]; //12 bytes for encoding data
    

    return nullptr;
}
