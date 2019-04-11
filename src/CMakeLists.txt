cmake_minimum_required(VERSION 2.8)
include_directories( ${OpenCV_INCLUDE_DIRS} )
find_package( OpenCV REQUIRED )
if( OpenCV_FOUND )
    list( APPEND ThirdParty_LIBS ${OpenCV_LIBS} )
    include_directories( ${OpenCV_INCLUDE_DIRS} )
endif( OpenCV_FOUND )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
