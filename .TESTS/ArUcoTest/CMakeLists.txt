cmake_minimum_required(VERSION 3.12)
project(arucotest)

set(OpenCV_STATIC ON)
set(OpenCV_RUNTIME vc16)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} "./headers" "../../../headers")
link_directories(${OpenCV_LIB_DIR})


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(arucotest "./main.cpp" "./source/ArUcoTest.cpp" "../../../source/RArUcoReader.cpp" "../../../source/RArUcoTag.cpp" "../../../source/RArUcoReader.cpp" "../../../source/RPiCamera.cpp" ) 

target_link_libraries(arucotest PRIVATE ${OpenCV_LIBS})
target_include_directories(arucotest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS})

