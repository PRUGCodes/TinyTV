cmake_minimum_required(VERSION 3.0.0)
project(TinyTV VERSION 0.1.0)
set(CXX_STANDARD 20)

include(CTest)
enable_testing()

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(TinyTV 
    ./src/main.cpp 
    ./src/serialComm.cpp
    ./include/serialComm.hpp)

target_link_libraries(TinyTV ${OpenCV_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)