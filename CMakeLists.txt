cmake_minimum_required(VERSION 3.17)
project(satellite)

set(CMAKE_CXX_STANDARD 14)

# Include GPSTk library
link_directories(/usr/local/gpstk/lib)
include_directories(/usr/local/gpstk/include/gpstk)

target_link_libraries(satellite gpstk)