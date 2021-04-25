#ifndef SATELLITE_ANGLES_H
#define SATELLITE_ANGLES_H

#include "../rinex/RinexObs.h"
#include "../sp3/SP3.h"
#include "../utils/Angles.h"

#include <Position.hpp>

using namespace std;
using namespace gpstk;

/**
 * Calculate angle between satellite and station.
 *
 * @param satellite Position of satellite.
 * @param station Position of station.
 * @return Angle between satellite and station.
 */
double getSatelliteStationAngle(const Position& satellite, const Position& station, const Position& stationNormal) {
    // Get vector for satellite
    std::vector<double> satelliteVector = {
            satellite.getX() - station.getX(),
            satellite.getY() - station.getY(),
            satellite.getZ()  - station.getZ()
    };

    double numeratorAngle =
            satelliteVector[0] * stationNormal.getX() +
            satelliteVector[1] * stationNormal.getY() +
            satelliteVector[2] * stationNormal.getZ();

    double denominatorAngle = sqrt(
            pow(satelliteVector[0], 2)
            + pow(satelliteVector[1], 2)
            + pow(satelliteVector[2], 2));

    double angle = numeratorAngle / denominatorAngle;

    return angle;
}

/**
 * Calculate angle between satellite and station.
 *
 * @param sp3 Satellite SP3 instance.
 * @param rinex Station Rinex instance.
 * @param filenameOut Path to output file with angles.
 * @param filenameTimeOut Path to output file with time.
 */
void satelliteStationAngle(SP3 sp3, RinexObs rinex, char* filenameOut) {
    // Get antenna (station) name and position
    string antennaName;
    vector<double> antennaPosition;

    tie(antennaName, antennaPosition) = rinex.getAntennaPosition();
    Position station (antennaPosition[0], antennaPosition[1], antennaPosition[2]);

    // Get n-vector for station coordinates (forward to Zenit)
    Position stationNormal = nVector(station.geocentricLatitude(), station.longitude());

    // Get time when antenna receive signal from satellite
    vector<int> timeObs = rinex.getTimeObs();

    // Get coordinates satellite and time from SP3 file
    map<int, vector<double>> coordinatesTime = sp3.getCoordinates();

    // Save angles ant time to file
    ofstream anglesFile;

    anglesFile.open(filenameOut);

    // Filter coordinates_time by time_obs
    auto it = coordinatesTime.begin();
    for (int i = 0; it != coordinatesTime.end(); it++, i++) {
        // If time from time_obs not found in coordinates_time, then we'll delete it
        if (find(timeObs.begin(), timeObs.end(), it->first) == timeObs.end()) {
            coordinatesTime.erase(it->first);
        }
    }

    // Get angles between satellite and station and save to files
    map<int, double> angleAndTime;
    it = coordinatesTime.begin();
    for (int i = 0; it != coordinatesTime.end(); it++, i++) {
        // Set position x, y, z
        Position satellite (it->second[0], it->second[1], it->second[2]);

        // Save angle between satellite and station for every time stamp
        anglesFile << it->first << "," << getSatelliteStationAngle(satellite, station, stationNormal) << endl;
    }
}

#endif //SATELLITE_ANGLES_H
