cmake_minimum_required(VERSION 3.12)
project(autoforktest)

add_compile_definitions(WIN32_LEAN_AND_MEAN)
add_compile_definitions(NEW_OPENCV_CONF)
add_compile_definitions(WIN4618)

set(OpenCV_RUNTIME vc17)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} "./headers" "../../headers" "../../shared/headers" "../../shared/headers/ext")
link_directories(${OpenCV_LIB_DIR})


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(autoforktest "./main.cpp" "./source/AutoForkTest.cpp" "../../client/source/RAutoFork.cpp" "../../client/source/RPiCamera.cpp" "../../client/source/RArucoReader.cpp" "../../client/source/RArucoTag.cpp" "../../client/source/RArucoTag3.cpp" "../../client/source/RCoordinateHelper.cpp" "../../client/source/ext/getstuff.cpp" "../../shared/source/ext/Client.cpp") 

target_link_libraries(autoforktest PRIVATE ${OpenCV_LIBS})
target_include_directories(autoforktest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS})

#set(THREADS_PREFER_THREAD_FLAG ON)
#find_package(Threads REQUIRED)
#target_link_libraries(autoforktest PRIVATE Threads::Threads)