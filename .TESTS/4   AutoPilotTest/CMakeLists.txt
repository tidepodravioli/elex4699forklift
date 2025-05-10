cmake_minimum_required(VERSION 3.12)
project(autopilottest)

# add_compile_definitions(NEW_OPENCV_CONF)
add_compile_definitions(PI4618)

set(OpenCV_RUNTIME vc17)
find_package(OpenCV REQUIRED)

find_library(PIGPIO_LIB NAMES pigpio REQUIRED)
find_library(PIGPIOD_IF2_LIB NAMES pigpiod_if2 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} "./headers" "../../../headers" "../../../shared/headers" "../../../shared/headers/ext")
link_directories(${OpenCV_LIB_DIR})


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(autopilottest "./main.cpp" "./source/AutoPilotTest.cpp" "../../../source/RAutoPilot.cpp" "../../../source/RCoordinateHelper.cpp" "../../../source/RMotorDriver.cpp" "../../CLIENT/source/ext/getstuff.cpp" "../../../source/RArUcoReader.cpp" "../../../source/RArUcoTag.cpp" "../../../source/RArUcoTag3.cpp"  "../../../shared/source/ext/Client.cpp" "../../../source/RPiHMotor.cpp") 

target_link_libraries(autopilottest PRIVATE ${OpenCV_LIBS} ${PIGPIO_LIB} ${PIGPIOD_IF2_LIB})
target_include_directories(autopilottest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS})

set(THREADS_PREFER_THREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(autopilottest PRIVATE Threads::Threads)