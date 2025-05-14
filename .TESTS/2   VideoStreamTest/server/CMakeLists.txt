cmake_minimum_required(VERSION 3.12)
project(vidservertest)

set(OpenCV_STATIC ON)
set(OpenCV_RUNTIME vc16)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} "./headers" "../../../headers" "../../../CLIENT/headers")
link_directories(${OpenCV_LIB_DIR})


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(vidservertest "./main.cpp" "./source/RCameraServer.cpp" "../../../source/RVidStream.cpp" "../../../CLIENT/source/RPiCamera.cpp" "../../../CLIENT/source/RArUcoReader.cpp" "../../../CLIENT/source/RArUcoTag.cpp" "../../../CLIENT/source/RArUcoTag3.cpp") 

target_link_libraries(vidservertest PRIVATE ${OpenCV_LIBS})
target_include_directories(vidservertest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS})

set(THREADS_PREFER_THREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(vidservertest PRIVATE Threads::Threads)
