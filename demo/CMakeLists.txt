cmake_minimum_required(VERSION 3.6)
project(demo)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
#find_package(Threads)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")
add_executable(demo ${SOURCE_FILES})
#target_link_libraries(demo  ${CMAKE_THREAD_LIBS_INIT})