#include "SP3.h"

#include <Position.hpp>
#include <HelmertTransform.hpp>

#include "../utils/Lagrange.h"

using namespace std;
using namespace gpstk;

SP3::SP3(char *filename, int PRNCode, int interpolateOrder) {
    this->filename = filename;
    this->PRNCode = PRNCode;
    this->interpolateOrder = interpolateOrder;

    file.open(this->filename, ios::in);

    SP3Header header;
    file >> header;
}

void SP3::getCoordinates(char *filenameOut) {
    SP3Stream rout(filenameOut, ios::out|ios::trunc);

    SP3Data data;
    SP3SatID satId(this->PRNCode, SatelliteSystem::GPS);

    while (file >> data) {
        // Find data for selected Satellite ID
        if (data.sat == satId) {
            CivilTime civilTime(data.time);

            Position pos(data.x[0], data.x[1], data.x[1]);
            pos.asGeodetic();

            int timestamp = int(civilTime.convertToCommonTime().getSecondOfDay());

            rout << timestamp << "," << pos.X() << "," << pos.Y() << "," << pos.Z() << endl;
        }
    }
}

std::map<int, std::vector<double>> SP3::getCoordinates() {
    SP3Data data;
    SP3SatID satId(this->PRNCode, SatelliteSystem::GPS);

    map<int, vector<double>> coordinatesTime;

    while (file >> data) {
        if (data.sat == satId) {
            CivilTime civilTime(data.time);
            int timestamp = int(civilTime.convertToCommonTime().getSecondOfDay());

            coordinatesTime[timestamp] = vector<double> {data.x[0] * 1000, data.x[1] * 1000, data.x[2] * 1000};
        }
    }

    return coordinatesTime;
}

void SP3::convertFrameCoordinates(transformElements tfElem, char *filenameOut) {
    // Get coordinates satellite and time from SP3 file
    map<int, vector<double>> coordinatesTime = this->getCoordinates();

    // Save coordinate and time to file
    ofstream coordinatesFile(filenameOut);

    HelmertTransform ht(
            tfElem.from, tfElem.to,
            tfElem.Rx, tfElem.Ry, tfElem.Rz,
            tfElem.Tx, tfElem.Ty, tfElem.Tz,
            tfElem.Scale, tfElem.Desc, tfElem.epoch);

    for (auto const& x : coordinatesTime) {
        Position orig_coord(x.second[0], x.second[1], x.second[2]);
        orig_coord.setReferenceFrame(ReferenceFrame::ITRF);

        Position result_coord(0, 0, 0);

        ht.transform(orig_coord, result_coord);

        coordinatesFile
            << x.first << "," << result_coord.X() << ',' << result_coord.Y() << ',' << result_coord.Z() << endl;
    }

    coordinatesFile.close();
}

gpstk::Triple SP3::getInterpolatedPosition(int secs) {
    map<int, vector<double>> coordinatesTime = this->getCoordinates();
    int n = interpolateOrder;

    int size = coordinatesTime.size();

    if (n % 2 != 0) {
        throw std::invalid_argument("Secs can't be < 0 or > 85500");
    }

    if (secs < 0 || secs > 85500) {
        throw std::invalid_argument("Secs can't be < 0 or > 85500");
    }

    int st = 0;
    for (auto it = coordinatesTime.begin(); it != coordinatesTime.end(); it++) {
        auto nx = std::next(it, 1);
        if ((it->first == secs) || (it->first < secs && nx->first > secs)) {
            break;
        }
        st++;
    }

    int n2 = n / 2;
    int ost = 0;

    int start = st - n2;
    if (start < 0) {
        ost = abs(start);
        start = 0;
    }

    int ost2 = 0;
    int end = st + n2 + ost;
    if (end > size) {
        ost2 = end - size;
        end = size;
    }

    start = start - ost2;

    double x, y, z;

    double* t = new double[n+1];
    double* xt = new double[n+1];
    double* yt = new double[n+1];
    double* zt = new double[n+1];

    int i = 0;
    int a = 0;
    for (auto const& x : coordinatesTime) {
        if (a < start || a > end) {
            a++;
            continue;
        }

        t[i] = x.first;
        xt[i] = x.second[0];
        yt[i] = x.second[1];
        zt[i] = x.second[2];

        i++;
        a++;
    }

    x = interpolate(t, xt, secs, n);
    y = interpolate(t, yt, secs, n);
    z = interpolate(t, zt, secs, n);

    Triple k(x, y, z);

    delete[] t;
    delete[] xt;
    delete[] yt;
    delete[] zt;

    return k;
}
