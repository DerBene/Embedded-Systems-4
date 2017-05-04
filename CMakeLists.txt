cmake_minimum_required(VERSION 3.6)
project(Embedded_Systems_4)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp src/PoolAllocator.cpp include/PoolAllocator.h)
add_executable(Embedded_Systems_4 ${SOURCE_FILES})