cmake_minimum_required(VERSION 3.16)
project(Satellite)

link_directories(/usr/local/gpstk/lib)
include_directories(/usr/local/gpstk/include/gpstk)

set(CMAKE_CXX_STANDARD 14)


add_executable(Satellite main.cpp)
target_link_libraries(Satellite gpstk)