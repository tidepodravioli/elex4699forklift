cmake_minimum_required(VERSION 3.12)
project(arucocalibration)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} "./headers")
link_directories(${OpenCV_LIB_DIR})


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(arucocalibration "./main.cpp" "./source/RCameraCalibration.cpp") 

target_link_libraries(arucocalibration PRIVATE ${OpenCV_LIBS})
target_include_directories(arucocalibration PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS})

