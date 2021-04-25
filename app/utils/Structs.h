#ifndef SATELLITE_STRUCTS_H
#define SATELLITE_STRUCTS_H

#include <CommonTime.hpp>
#include <ReferenceFrame.hpp>

struct Station {
    double latitude;
    double longitude;

    double x;
    double y;
    double z;
};

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

struct ConfigRun {
    int PRNCode;
    std::string obsCode;

    Station station;

    char * rinex_file_first;
    char * rinex_file_second;

    char * sp3_file;

    char * fileOutProjections;
    char * fileOutSlipsProjections;
};

struct Plane {
    double A;
    double B;
    double C;
    double D;
};


struct Data {
    int t;
    double x;
};

#endif //SATELLITE_STRUCTS_H
