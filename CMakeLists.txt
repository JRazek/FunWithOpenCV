cmake_minimum_required(VERSION 3.16)
project(OpenCV)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

#set(CMAKE_CXX_COMPILER "/usr/bin/arm-linux-gnueabihf-g++-9")

#set(CMAKE_CXX_COMPILER "/usr/bin/g++")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#set(CMAKE_SYSTEM_NAME Linux)
#set(CMAKE_SYSTEM_VERSION 1)
#set(CMAKE_EXE_LINKER_FLAGS "-static")
#set(CMAKE_SYSTEM_PROCESSOR "arm")
#set(CMAKE_CXX_COMPILER "/usr/bin/arm-linux-gnueabihf-g++-9")
#set(CMAKE_C_COMPILER "/usr/bin/arm-linux-gnueabihf-gcc-9")


add_executable(OpenCV main.cpp Tests/TestingClass.cpp utils/ByteImage.cpp utils/ByteImage.h)

target_link_libraries( OpenCV ${OpenCV_LIBS} )