#include <iostream>
#include <thread>
#include <opencv2/opencv.hpp>
#include "Tests/TestingClass.h"

int main() {
    //TestingClass::imageDilation();

    std::thread t1(&TestingClass::longFunction);
    for(int i = 0; i < 1e6; i ++){
        if(!(i % 1000)){
            std::cout<<":) \n";
        }
    }

    t1.join();
   // std::cerr<<"test";
    return 0;
}
