//
// Created by user on 16.07.2021.
//

#ifndef OPENCV_BYTEIMAGE_H
#define OPENCV_BYTEIMAGE_H


#include <opencv2/core/mat.hpp>

typedef unsigned char byte;

class ByteImage {
private:

public:
    const static inline u_int8_t imageMetadataSize = 6;
    static cv::Mat decodeImage(byte *image);
    static byte *encodeImage(const cv::Mat &img);
    static unsigned int getDataSize(const byte *bytes);
};


#endif //OPENCV_BYTEIMAGE_H
