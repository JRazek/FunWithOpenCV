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

add_executable(OpenCVTransfersServer serverRun.cpp utils/ByteImage.cpp utils/ByteImage.h Server/Server.cpp Server/Server.h )
add_executable(OpenCVTransfersClient clientRun.cpp utils/ByteImage.cpp utils/ByteImage.h )

target_link_libraries(OpenCVTransfersServer ${OpenCV_LIBS})

target_link_libraries(OpenCVTransfersServer $ENV{HOME}/CLionProjects/TCProtocols/build/libTCProtocols.a)

target_link_libraries(OpenCVTransfersClient ${OpenCV_LIBS})

target_link_libraries(OpenCVTransfersClient $ENV{HOME}/CLionProjects/TCProtocols/build/libTCProtocols.a)
