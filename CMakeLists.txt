cmake_minimum_required(VERSION 3.16)
project(OpenCV)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


add_executable(OpenCV main.cpp Tests/TestingClass.cpp Tests/TestingClass.h)

target_link_libraries( OpenCV ${OpenCV_LIBS} )