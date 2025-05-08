cmake_minimum_required(VERSION 3.12)
project(cameratest)

# comment this line out if using an older version of OpenCV
add_compile_definitions(NEW_OPENCV_CONF)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} "./headers" "../../../headers")
link_directories(${OpenCV_LIB_DIR})


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(cameratest "./main.cpp" "./source/cameratest.cpp" "../../../source/RArUcoReader.cpp" "../../../source/RArUcoTag.cpp" "../../../source/RArUcoReader.cpp" "../../../source/RPiCamera.cpp" ) 

target_link_libraries(cameratest PRIVATE ${OpenCV_LIBS})
target_include_directories(cameratest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS})

