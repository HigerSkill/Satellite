#ifndef SATELLITE_PROJECTION_H
#define SATELLITE_PROJECTION_H

#include <vector>

#include "SP3.h"

#include "../constants.h"
#include "../utils/Structs.h"

class Projection {
private:
    SP3 &sp3;
    Station station;
    Plane plane;

    /**
     * Find plane by station normal (Zenit) vector.
    */
    Plane findPlane();

    /**
     * Find projection point on plane.
     *
     * @param point Position of point which will be projected.
    */
    gpstk::Position findProjection(gpstk::Position point);

public:
    /**
     * Constructor create Projection object.
     *
     * @param sp3 SP3Parser object.
    */
    Projection(SP3 &sp3, Station station);

    /**
     * Get projections for coordinates in SP3 file and write to the file.
     *
     * */
    void getProjections(char *filenameOut);


    /**
     * Get projections for coordinates in SP3 file.
     *
     * */
    void getProjections(char *filenameOut,  const std::vector<int>& times, const std::string& mode = "a");

};


#endif //SATELLITE_PROJECTION_H
