cmake_minimum_required(VERSION 3.16)
project(Satellite)

link_directories(/usr/local/lib)

# Change path to gpstk
include_directories(../../gpstk-2.12-gcc7_0/include/gpstk)

set(CMAKE_CXX_STANDARD 14)


add_executable(Satellite main.cpp)
target_link_libraries(Satellite gpstk)