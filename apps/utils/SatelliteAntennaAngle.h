#ifndef SATELLITE_SATELLITEANTENNAANLGE_H
#define SATELLITE_SATELLITEANTENNAANLGE_H

#include "../Rinex/RinexParser.h"
#include "../SP3/SP3Parser.h"

/**
 * Calculate n-vector for latitude and longitude of station.
 * Equation is exact both for spherical and ellipsoidal Earth model.
 *
 * @param latitude
 * @param longitude
 * @return Coordinates of n-vector.
 */
Position nVector(double latitude, double longitude) {
    double a = cos(latitude) * cos(longitude);
    double b = cos(latitude) * sin(longitude);
    double c = sin(latitude);

    Position normal(a, b, c, Position::Cartesian);

    return normal;
}

/**
 * Calculate angle between satellite and station.
 *
 * @param satellite Position of satellite.
 * @param station Position of station.
 * @return Angle between satellite and station.
 */
double satelliteStationAngle(const Position& satellite, const Position& station) {
    // Get n-vector for station coordinates
    Position stationNormal = n_vector(station.getGeodeticLatitude() * PI / 180, station.getLongitude() * PI / 180);

    // Get vector for satellite
    vector<double> satelliteVector = {
            satellite.getX() * 1000 - station.getX(),
            satellite.getY() * 1000 - station.getY(),
            satellite.getZ() * 1000 - station.getZ()
    };

    double numeratorAngle =
            satelliteVector[0] * stationNormal.getX() +
            satelliteVector[1] * stationNormal.getY() +
            satelliteVector[2] * stationNormal.getZ();

    double denominatorAngle = sqrt(pow(satelliteVector[0], 2) + pow(satelliteVector[1], 2) + pow(satelliteVector[2], 2));
    double angle = acos(numeratorAngle / denominatorAngle) * 180 / PI;

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
void satelliteStationAngle(SP3Parser sp3, RinexParser rinex, char* filenameOut, char* filenameTimeOut) {
    // Get antenna (station) name and position
    string antennaName;
    vector<double> antennaPosition;

    tie(antennaName, antennaPosition) = rinex.getAntennaPosition();
    Position station (antennaPosition[0], antennaPosition[1], antennaPosition[2]);

    // Get time when antenna receive signal from satellite
    vector<int> timeObs = rinex.getTimeObs();

    // Get coordinates satellite and time from SP3 file
    map<int, vector<double>> coordinatesTime = sp3.getCoordinates();

    // Save angles ant time to file
    ofstream anglesFile;
    ofstream timeFile;

    anglesFile.open(filenameOut);
    timeFile.open(filenameTimeOut);

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
        timeFile << it->first << endl;
        anglesFile << satellite_station_angle(satellite, station) << endl;
    }
}

#endif //SATELLITE_SATELLITEANTENNAANLGE_H
