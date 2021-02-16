//
// Created by alex on 2/10/21.
//

#ifndef SATELLITE_SP3PARSER_H
#define SATELLITE_SP3PARSER_H

#include "utils.h"

#include <map>
#include <vector>
#include <PositionSatStore.hpp>

class SP3Parser {
private:
    char* filename;
    int PRNCode;

public:
    /**
     * Constructor create SP3Parser object.
     *
     * @param filename Path to SP3 file.
     * @param prnCode PRN code of satellite.
    */
    SP3Parser(char *filename, int PRNCode);

    /**
     * Parse sp3 file and write time and coordinates in files.
     * Get the three-vector for position | velocity (m | dm/s).
     *
     * @param filenameOut Name of output file where will be coordinates.
     * @param filenameTimeOut Name of out file where will be time..
    */
    void getCoordinates(char* filenameOut, char* filenameTimeOut);

    /**
     * Parse sp3 file and write time and coordinates.
     * Get the three-vector for position | velocity (m | dm/s).
     *
     * @return Map of time and coordinates.
     */
    std::map<int, std::vector<double>> getCoordinates();

    /**
     * Get position and interpolate with Lagrange interpolation.
     *
     * @return PositionSatStore with interpolated coordinates.
    */
    gpstk::PositionSatStore getPositionStore(int interpolateOrder=10);

    /**
     * Convert reference frame for SP3 coordinates.
     *
     * @param sp3 Satellite SP3 instance.
     * @param filenameOut Path to output file with angles.
     * @param filenameTimeOut Path to output file with time.
     */
    void convertFrameCoordinates(transformElements tfElem, char* filenameOut, char* filenameTimeOut);
};


#endif //SATELLITE_SP3PARSER_H
