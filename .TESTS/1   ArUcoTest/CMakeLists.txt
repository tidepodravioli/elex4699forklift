cmake_minimum_required(VERSION 3.12)
project(arucotest)

# comment this line out if using an older version of OpenCV
add_compile_definitions(NEW_OPENCV_CONF)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} "./headers" "../../../headers" "../../../CLIENT/headers")
link_directories(${OpenCV_LIB_DIR})


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(arucotest "./main.cpp" "./source/ArUcoTest.cpp" "../../../CLIENT/source/RArUcoReader.cpp" "../../../CLIENT/source/RArUcoTag.cpp" "../../../CLIENT/source/RArUcoReader.cpp" ) 

target_link_libraries(arucotest PRIVATE ${OpenCV_LIBS})
target_include_directories(arucotest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS})

