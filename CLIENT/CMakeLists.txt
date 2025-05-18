# CMAKELISTS.TXT FOR ELEX4699 FORKLIFT CLIENT
# WRITTEN FOR WINDOWS BY RAFAEL BANALAN
# 2025-04-30

cmake_minimum_required(VERSION 3.12)
project(elex4699forklift_client)

add_compile_definitions(WIN4618)
add_compile_definitions(NEW_OPENCV_CONF)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} "./headers" "./headers/ext" "../shared/headers" "../shared/headers/ext")
link_directories(${OpenCV_LIB_DIR})


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "./source/*.cpp" "./source/RForkliftClient/*.cpp" "./source/ext/*.cpp" "../shared/source/*.cpp" "../shared/source/ext/*.cpp")
add_executable(elex4699forklift_client ${SOURCES} "./main.cpp") 

target_link_libraries(elex4699forklift_client PRIVATE ${OpenCV_LIBS})
target_include_directories(elex4699forklift_client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS})

