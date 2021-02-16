cmake_minimum_required(VERSION 3.17)
project(satellite)

set(CMAKE_CXX_STANDARD 14)

link_directories(/usr/local/gpstk/lib)
include_directories(/usr/local/gpstk/include/gpstk)

add_executable(
        Satellite main.cpp
        apps/Rinex/RinexParser.h
        apps/Rinex/RinexParser.cpp
        apps/utils/files.h
        apps/SP3/SP3Parser.cpp
        apps/SP3/SP3Parser.h
        apps/utils/SatelliteAntennaAngle.h
        apps/SP3/utils.h
        apps/Rinex/CycleSlipDetection.cpp
        apps/Rinex/CycleSlipDetection.h
)
target_link_libraries(Satellite gpstk)
