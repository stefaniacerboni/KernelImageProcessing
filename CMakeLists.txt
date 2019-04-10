cmake_minimum_required(VERSION 3.9)
project(PBM)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
set(CMAKE_CXX_STANDARD 11)
add_executable(PBM main.cpp img.pbm logo.bmp marbles.pbm marbles1.pbm Vd-Orig.pbm kip.cpp kip.h Image.cpp Image.h)

target_link_libraries( PBM ${OpenCV_LIBS} )