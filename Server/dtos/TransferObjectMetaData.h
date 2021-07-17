//
// Created by user on 17.07.2021.
//

#ifndef OPENCV_TRANSFEROBJECTMETADATA_H
#define OPENCV_TRANSFEROBJECTMETADATA_H

#include <zconf.h>

typedef unsigned short u_short;
typedef unsigned char byte;

struct TransferObjectMetaData {
    const static u_short metaDataSize = 8;
    u_int8_t dataSize;
    TransferObjectMetaData(const byte *metaData){
        
    }
};


#endif //OPENCV_TRANSFEROBJECTMETADATA_H
