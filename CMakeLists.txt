cmake_minimum_required(VERSION 3.17)
project(Satellite)

set(CMAKE_CXX_STANDARD 14)

# Include GPSTk library
link_directories(/usr/local/gpstk/lib)
include_directories(/usr/local/gpstk/include/gpstk)

add_executable(
    Satellite main.cpp
    app/rinex/RinexObs.h
    app/rinex/RinexObs.cpp
    app/rinex/CycleSlipDetection.cpp
    app/rinex/CycleSlipDetection.h
    app/rinex/MovingAverage.cpp
    app/rinex/MovingAverage.h
    app/sp3/SP3.cpp
    app/sp3/SP3.h
    app/utils/Structs.h
    app/utils/Lagrange.h
    app/sp3/Projection.cpp
    app/sp3/Projection.h
    app/constants.h
    app/utils/Vectors.h
    app/utils/Angles.h
    runs/find_slips.cpp
    app/utils/Slips.h
#    runs/sp3_projections.cpp
#    runs/sp3_projections_period.cpp
#    runs/sp3_read.cpp
)

target_link_libraries(Satellite gpstk)