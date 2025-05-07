cmake_minimum_required(VERSION 3.12)
project(cameraclienttest)

set(OpenCV_RUNTIME vc17)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} "./headers" "../../../headers")
link_directories(${OpenCV_LIB_DIR})


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(cameraclienttest ${SOURCES} "./main.cpp" "./source/RCameraClient.cpp" "../../../../CLIENT/source/RVidReceiver.cpp") 

target_link_libraries(cameraclienttest PRIVATE ${OpenCV_LIBS})
target_include_directories(cameraclienttest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS})

