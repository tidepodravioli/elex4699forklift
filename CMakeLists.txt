# CMAKELISTS.TXT FOR ELEX4699 FORKLIFT SERVER
# WRITTEN FOR RPIOS BY RAFAEL BANALAN
# 2025-04-29

cmake_minimum_required(VERSION 3.12)
project(forkliftserver)

add_compile_definitions(PI4618)

set(OpenCV_STATIC ON)
set(OpenCV_RUNTIME vc17)
find_package(OpenCV REQUIRED)

find_library(PIGPIO_LIB NAMES pigpio REQUIRED)
find_library(PIGPIOD_IF2_LIB NAMES pigpiod_if2 REQUIRED)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

include_directories(${OpenCV_INCLUDE_DIRS} "./headers" "./headers/ext" "./shared/headers" "./shared/headers/ext")
link_directories(${OpenCV_LIB_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "./source/*.cpp" "./source/RForkliftManager/*.cpp" "./source/ext/*.cpp" "./shared/source/*.cpp" "./shared/source/ext/*.cpp")
add_executable(forkliftserver ${SOURCES} "./main.cpp") 

target_link_libraries(forkliftserver PRIVATE ${OpenCV_LIBS} ${PIGPIO_LIB} ${PIGPIO_IF2_LIB} ${CURSES_LIBRARIES})
target_include_directories(forkliftserver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS})

set(THREADS_PREFER_THREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(forkliftserver PRIVATE Threads::Threads)

