cmake_minimum_required(VERSION 3.16)
project(OpenCV)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

#set(CMAKE_CXX_COMPILER "/usr/bin/arm-linux-gnueabihf-g++-9")

#set(CMAKE_CXX_COMPILER "/usr/bin/g++")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories($ENV{HOME}/CLionProjects/TCProtocols)

add_executable(OpenCV main.cpp Tests/TCPController.cpp utils/ByteImage.cpp utils/ByteImage.h )

target_link_libraries( OpenCV ${OpenCV_LIBS} )

target_link_libraries(OpenCV $ENV{HOME}/CLionProjects/TCProtocols/cmake-build-debug/libTCProtocols.a)
