#ifndef SATELLITE_UTILS_H
#define SATELLITE_UTILS_H

#include <CommonTime.hpp>
#include <ReferenceFrame.hpp>

struct transformElements {
    gpstk::ReferenceFrame from;
    gpstk::ReferenceFrame to;

    double Rx;
    double Ry;
    double Rz;

    double Tx;
    double Ty;
    double Tz;

    double Scale;

    std::string Desc;

    gpstk::CommonTime epoch;
};

#endif //SATELLITE_UTILS_H
