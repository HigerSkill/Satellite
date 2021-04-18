#ifndef SATELLITE_SP3_H
#define SATELLITE_SP3_H

#include <map>
#include <vector>
#include <PositionSatStore.hpp>
#include <SP3Stream.hpp>


#include "./utils.h"


class SP3 {
public:
    char* filename;
    int PRNCode;
    int interpolateOrder = 10;

    gpstk::SP3Stream file;
    gpstk::SP3Header header;

    /**
     * Constructor create SP3 object.
     *
     * @param filename Path to SP3 file.
     * @param PRNCode PRN code of satellite.
     * @param interpolateOrder Order of the Lagrange Polinom.
    */
    SP3(char *filename, int PRNCode, int interpolateOrder);

/**
     * Parse SP3 file and write time and coordinates in files.
     * Get the three-vector for position | velocity (m | dm/s).
     *
     * @param filenameOut Name of output file where will be timestamps and coordinates.
    */
    void getCoordinates(char* filenameOut);

    /**
     * Parse sp3 file and write time and coordinates.
     * Get the three-vector for position | velocity (m | dm/s).
     *
     * @return Map of time and coordinates.
     */
    std::map<int, std::vector<double>> getCoordinates();

    /**
     * Convert reference frame for SP3 coordinates.
     *
     * @param sp3 Satellite SP3 instance.
     * @param filenameOut Path to output file with angles.
     */
    void convertFrameCoordinates(transformElements tfElem, char* filenameOut);

    /**
     * Get interpolated SP3 coordinates.
     *
     * @param secs.
     *
     * @return Interpolated coordinates.
     */
    gpstk::Triple getInterpolatedPosition(int secs);


};


#endif //SATELLITE_SP3_H
