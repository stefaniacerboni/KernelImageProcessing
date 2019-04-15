cmake_minimum_required(VERSION 2.8)
project(runUnitTests)
find_package( OpenCV REQUIRED )
if( OpenCV_FOUND )
    list( APPEND ThirdParty_LIBS ${OpenCV_LIBS} )
    include_directories( ${OpenCV_INCLUDE_DIRS} )
endif( OpenCV_FOUND )
include_directories( ${OpenCV_INCLUDE_DIRS} )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(runUnitTests testImage.cpp ../src/kip.h ../src/kip.cpp ../src/Image.cpp ../src/Image.h testKIP.cpp)
#Link with GoogleTest
target_link_libraries(runUnitTests gtest gtest_main)
target_link_libraries(runUnitTests ${log-lib} ${OpenCV_LIBS} )
#Link with GoogleMock
target_link_libraries(runUnitTests gmock gmock_main)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})