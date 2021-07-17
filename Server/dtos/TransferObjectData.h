//
// Created by user on 17.07.2021.
//

#ifndef OPENCV_TRANSFEROBJECTDATA_H
#define OPENCV_TRANSFEROBJECTDATA_H

#include <zconf.h>
#include <algorithm>

typedef unsigned short u_short;
typedef unsigned char byte;

struct TransferObjectData {
    const static u_short metaDataSize = 8;
    u_int64_t dataSize;
    byte *decodedData;
    TransferObjectData(const byte *objectEncoded){
        this->dataSize = 0;

        for(int i = 0; i < metaDataSize; i ++){
            this->dataSize += ((u_int64_t)objectEncoded[i] << metaDataSize * (7 - i));
        }
        decodedData = new byte [dataSize];
        std::copy(objectEncoded + metaDataSize, objectEncoded + metaDataSize + dataSize, decodedData);
    }


    static byte *encode(u_int64_t dataSize, const byte *dataRaw){
        byte *data = new byte [dataSize + metaDataSize];


        for(int i = 0; i < metaDataSize; i ++){
            data[i] = (dataSize >> metaDataSize*(7 - i));
        }

        std::copy(dataRaw, dataRaw + dataSize, data + metaDataSize);

        return data;
    }
};


#endif //OPENCV_TRANSFEROBJECTDATA_H
