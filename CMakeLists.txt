cmake_minimum_required(VERSION 3.16)
project(OpenCVTransfers)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

#set(CMAKE_CXX_COMPILER "/usr/bin/arm-linux-gnueabihf-g++-9")

#set(CMAKE_CXX_COMPILER "/usr/bin/g++")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories($ENV{HOME}/CLionProjects/TCProtocols)

#flag - if true - compile server otherwise compile client
if(false)
    add_executable(OpenCVTransfers serverRun.cpp utils/ByteImage.cpp utils/ByteImage.h Server/Server.cpp Server/Server.h )
else()
    add_executable(OpenCVTransfers clientRun.cpp utils/ByteImage.cpp utils/ByteImage.h )
endif()

target_link_libraries(OpenCVTransfers ${OpenCV_LIBS})

target_link_libraries(OpenCVTransfers $ENV{HOME}/CLionProjects/TCProtocols/build/libTCProtocols.a)
