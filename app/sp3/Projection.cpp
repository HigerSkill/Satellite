#include "Projection.h"

#include "../utils/Vectors.h"
#include "../utils/Angles.h"

using namespace std;
using namespace gpstk;

Projection::Projection(SP3 &sp3, Station station): sp3(sp3) {
    this->station = station;
}

Plane Projection::findPlane() {
    Position normal = nVector(station.latitude, station.longitude);

    double A = normal.X();
    double B = normal.Y();
    double C = normal.Z();

    double D = -A*station.x - B*station.y - C*station.z;

    this->plane = Plane{A, B, C, D};

    return this->plane;
}

Position Projection::findProjection(Position point) {
    double t = -(plane.A * point.X() + plane.B * point.Y() + plane.C * point.Z() + plane.D)
               / (pow(plane.A, 2) + pow(plane.B, 2) + pow(plane.C, 2));

    double Xp = plane.A * t + point.X();
    double Yp = plane.B * t + point.Y();
    double Zp = plane.C * t + point.Z();

    return Position(Xp, Yp, Zp);
}

void Projection::getProjections(char *filenameOut) {
    // Get plane for station normal vector
    findPlane();

    // Save angles ant time to file
    ofstream projections;
    projections.open(filenameOut, ios::out | ios::app);

    // Get n-vector for station coordinates (forward to Zenit)
    Position stationNormal = nVector(station.latitude, station.longitude);

    map<int, vector<double>> projectedCoordinates;
    map<int, vector<double>> coordinatesTime = sp3.getCoordinates();

    for (auto const& x : coordinatesTime) {

        Triple a(x.second[0], x.second[1], x.second[2]);

        Position satellite(x.second[0], x.second[1], x.second[2]);

        double angle = getSatelliteStationAngle(satellite, Position(station.x, station.y, station.z), stationNormal);

        // Get polar coordinate `r`
        double r = sin(angle);

        // Skip point if station doesn't see satellite
        if (angle > PI/2) continue;

        // Find North x East frame
        Position North = findProjection(POLAR_STAR);
        North = {North.X() - station.x, North.Y() - station.y, North.Z() - station.z};

        double absNorth = absVector(North);

        North = {North.X() / absNorth, North.Y() / absNorth, North.Z() / absNorth};

        Position East = vectorMultiply(North, stationNormal);

        double absEast = absVector(East);
        East = {East.X() / absEast, East.Y() / absEast, East.Z() / absEast};

        Position SatProjected = findProjection(satellite);
        Position SatVectorProjected = {
            SatProjected.X() - station.x,
            SatProjected.Y() - station.y,
            SatProjected.Z() - station.z
        };

        // Get cos(theta) and cos(sign)
        double cosTheta = getCosAngle(
                {East.X(), East.Y(), East.Z()},
                {SatVectorProjected.X(), SatVectorProjected.Y(), SatVectorProjected.Z()});

        double cosSign = getCosAngle(
                {SatVectorProjected.X(), SatVectorProjected.Y(), SatVectorProjected.Z()},
                {North.X(), North.Y(), North.Z()});


        double theta;
        // Get polar coordinate `theta`
        if (cosSign >= 0) {
            theta = acos(cosTheta);
        } else {
            theta = 2*PI - acos(cosTheta);
        }

        projectedCoordinates[x.first] = vector<double> {r, theta};

        projections << x.first << "," << r << "," << theta << endl;

    }

    projections.close();
}

void Projection::getProjections(char *filenameOut, const vector<int> &times, const string &mode) {
    // Get plane for station normal vector
    findPlane();

    ofstream projections;

    // Save angles ant time to file
    if (mode == "a") {
        projections.open(filenameOut, ios::app | ios::out);
    } else {
        projections.open(filenameOut, ios::out);
    }

    // Get n-vector for station coordinates (forward to Zenit)
    Position stationNormal = nVector(station.latitude, station.longitude);

    PositionSatStore coordinates;

    for (double t : times) {
        Triple position;

        try {
            position = this->sp3.getInterpolatedPosition(int(t));
        } catch(...) {
            continue;
        }

        Position satellite(position[0], position[1], position[2]);

        double angle = getSatelliteStationAngle(
                satellite,
                Position(station.x, station.y, station.z),
                stationNormal);

        // Get polar coordinate `r`
        double r = sin(angle);

        // Skip point if station doesn't see satellite
        if (angle > PI/2) {
            continue;
        }

        // Find North x East frame
        Position North = findProjection(POLAR_STAR);
        North = {North.X() - station.x, North.Y() - station.y, North.Z() - station.z};

        double absNorth = absVector(North);

        North = {North.X() / absNorth, North.Y() / absNorth, North.Z() / absNorth};

        Position East = vectorMultiply(North, stationNormal);

        double absEast = absVector(East);
        East = {East.X() / absEast, East.Y() / absEast, East.Z() / absEast};

        Position SatProjected = findProjection(satellite);
        Position SatVectorProjected = {
                SatProjected.X() - station.x,
                SatProjected.Y() - station.y,
                SatProjected.Z() - station.z
        };

        // Get cos(theta) and cos(sign)
        double cosTheta = getCosAngle(
                {East.X(), East.Y(), East.Z()},
                {SatVectorProjected.X(), SatVectorProjected.Y(), SatVectorProjected.Z()});

        double cosSign = getCosAngle(
                {SatVectorProjected.X(), SatVectorProjected.Y(), SatVectorProjected.Z()},
                {North.X(), North.Y(), North.Z()});


        double theta;
        // Get polar coordinate `theta`
        if (cosSign >= 0) {
            theta = acos(cosTheta);
        } else {
            theta = 2*PI - acos(cosTheta);
        }

        projections << t << "," << r << "," << theta << endl;

    }

    projections.flush();
    projections.close();
}
