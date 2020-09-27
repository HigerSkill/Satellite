#include <iostream>
#include <math.h>
#include <string>

#include "Position.hpp"

using namespace std;
using namespace gpstk;

Position v_normal(double latitude, double longitude) {
    /* Return n-vector for latitude and longitude.
     *
     * Equation is exact both for spherical and ellipsoidal Earth model.
     * */
    double a = cos(latitude) * cos(longitude);
    double b = cos(latitude) * sin(longitude);
    double c = sin(latitude);

    Position normal(a, b, c, Position::Cartesian);

    return normal;
}

double satellite_station_angle(
        const Position& satellite, const Position& station) {
    /* Return angle between satellite and station. */

//    ofstream station_file;
//    ofstream satellite_file;
//    station_file.open("station_normal", ios::out|ios::trunc);
//    satellite_file.open("satellite_vector", ios::out|ios::trunc);

    // Get n-vector for station coordinates
    Position station_normal = v_normal(station.getGeodeticLatitude(), station.getLongitude());
//    cout << station.getGeodeticLatitude() << endl;
//    cout << station.getLongitude() << endl;

    // Get vector for satellite
    vector<double> satellite_vector = {
        satellite.getX() - station.getX(),
        satellite.getY() - station.getY(),
        satellite.getZ() - station.getZ()
    };

    double numerator_angle =
            satellite_vector[0] * station_normal.getX() +
            satellite_vector[1] * station_normal.getY() +
            satellite_vector[2] * station_normal.getZ();

    double denominator_angle =
            sqrt(
                pow(satellite_vector[0], 2) +
                pow(satellite_vector[1], 2) +
                pow(satellite_vector[2], 2)
            );

    double angle = acos(numerator_angle / denominator_angle) * 180 / PI;

    return angle;
}

int satellite_station_angles_file(
        const string& satellite_positions_filename,
        const string& satellite_station_angles_filename,
        Position station) {
    /* Calculate and write angle between station and satellite in file. */

    ifstream sat_pos_file;
    sat_pos_file.open(satellite_positions_filename.c_str(), ios::in);

    ofstream angles_file;
    angles_file.open(satellite_station_angles_filename.c_str(), ios::out);

    double x, y, z;
    while (sat_pos_file >> x >> y >> z) {
        Position satellite(x, y, z, Position::Cartesian);

        double angle = satellite_station_angle(satellite, station);
        angles_file << angle << endl;
    }

    return 0;
}