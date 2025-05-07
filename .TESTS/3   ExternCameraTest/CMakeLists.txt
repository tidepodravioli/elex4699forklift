cmake_minimum_required(VERSION 3.12)
project(externcameratest)

add_compile_definitions(NEW_OPENCV_CONF)
add_compile_definitions(WIN4618)

set(OpenCV_RUNTIME vc17)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} "./headers" "../../../headers" "../../../shared/headers" "../../../shared/headers/ext")
link_directories(${OpenCV_LIB_DIR})


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(externcameratest "./main.cpp" "./source/ExternCameraTest.cpp" "../../../source/RExternCamera.cpp" "../../../source/RArUcoReader.cpp" "../../../source/RArUcoTag.cpp"  "../../../shared/source/ext/Client.cpp") 

target_link_libraries(externcameratest PRIVATE ${OpenCV_LIBS})
target_include_directories(externcameratest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS})