#include "SP3Parser.h"

#include <SP3Data.hpp>
#include <SP3Stream.hpp>
#include <CivilTime.hpp>
#include <Position.hpp>
#include <HelmertTransform.hpp>

using namespace gpstk;
using namespace std;

SP3Parser::SP3Parser(char *filename, int PRNCode) {
    this->filename = filename;
    this->PRNCode = PRNCode;
}

void SP3Parser::getCoordinates(char *filenameOut, char *filenameTimeOut) {
    SP3Stream sp3File(this->filename);
    SP3Stream rout(filenameOut, ios::out|ios::trunc);
    SP3Stream timeOut(filenameTimeOut, ios::out | ios::trunc);

    SP3Header header;
    sp3File >> header;
    rout.header = sp3File.header;

    SP3Data data;
    SP3SatID satId(this->PRNCode, SatelliteSystem::GPS);

    while (sp3File >> data) {
        // Find data for selected Satellite ID
        if (data.sat == satId) {
            CivilTime civilTime(data.time);

            rout << data.x[0] << "," << data.x[1] << "," << data.x[2] << endl;

            timeOut << civilTime << endl;
        }
    }

}

std::map<int, std::vector<double>> SP3Parser::getCoordinates() {
    SP3Stream sp3File(this->filename);

    SP3Header header;
    sp3File >> header;

    SP3Data data;
    SP3SatID satId(this->PRNCode, SatelliteSystem::GPS);

    map<int, vector<double>> coordinatesTime;

    while (sp3File >> data) {
        if (data.sat == satId) {
            CivilTime civilTime(data.time);
            int time = int(civilTime.convertToCommonTime().getSecondOfDay());

            coordinatesTime[time] = vector<double> {data.x[0], data.x[1], data.x[2]};
        }
    }

    return coordinatesTime;
}

gpstk::PositionSatStore SP3Parser::getPositionStore(int interpolateOrder) {
    PositionSatStore satStore = PositionSatStore();
    satStore.setInterpolationOrder(interpolateOrder);

    SP3Stream sp3File(this->filename);

    SP3Header header;
    sp3File >> header;

    SP3Data data;
    SP3SatID satId(this->PRNCode, SatelliteSystem::GPS);

    while (sp3File >> data) {
        if (data.sat == satId) {
            Triple coords(data.x[0], data.x[1], data.x[2]);

            satStore.addPositionData(satId, data.time, coords);
        }
    }

    return satStore;
}

void SP3Parser::convertFrameCoordinates(transformElements tfElem, char *filenameOut, char *filenameTimeOut) {
    // Get coordinates satellite and time from SP3 file
    map<int, vector<double>> coordinatesTime = this->getCoordinates();

    // Save coordinate ant time to file
    ofstream coordinatesFile;
    ofstream timeFile;

    coordinatesFile.open(filenameOut);
    timeFile.open(filenameTimeOut);

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

        coordinatesFile << result_coord.X() << ',' << result_coord.Y() << ',' << result_coord.Z() << endl;
        timeFile << x.first;
    }

    coordinatesFile.close();
    timeFile.close();
}
