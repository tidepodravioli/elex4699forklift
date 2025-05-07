cmake_minimum_required(VERSION 3.12)
project(vidservertest)

set(OpenCV_STATIC ON)
set(OpenCV_RUNTIME vc16)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} "./headers" "../../../headers")
link_directories(${OpenCV_LIB_DIR})


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(vidservertest "./main.cpp" "./source/RCameraServer.cpp" "../../../source/RVidStream.cpp" "../../../source/RPiCamera.cpp" ) 

target_link_libraries(vidservertest PRIVATE ${OpenCV_LIBS})
target_include_directories(vidservertest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS})

set(THREADS_PREFER_THREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(vidservertest PRIVATE Threads::Threads)
