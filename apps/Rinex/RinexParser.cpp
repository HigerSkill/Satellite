#include "RinexParser.h"
#include "../utils/files.h"

#include <Rinex3ObsStream.hpp>
#include <Rinex3ObsData.hpp>
#include <Rinex3NavStream.hpp>
#include <Rinex3NavData.hpp>

using namespace gpstk;
using namespace std;

RinexParser::RinexParser(char *filename, int PRNCode) {
    this->filename = filename;
    this->PRNCode = PRNCode;
}

vector<int> RinexParser::getTimeObs(void) {
    try {
        Rinex3ObsHeader header;
        Rinex3ObsData data;
        Rinex3ObsStream obsFile(this->filename);
        obsFile.exceptions(ios::failbit);

        vector<int> time;

        obsFile >> header;

        while (obsFile >> data) {
            CivilTime obsTime(data.time);
            RinexSatID satId(this->PRNCode, SatelliteSystem::GPS);

            auto pointer = data.obs.find(satId);

            if (pointer == data.obs.end()) {
                cout << "PRN " << satId << " not in view." << endl;
            } else {
                time.push_back(int(obsTime.convertToCommonTime().getSecondOfDay()));
            }
        }

        obsFile.close();

        return time;
    }
    catch(FFStreamError& error) {
        cout << error;
        exit(1);
    }
    catch(Exception& error) {
        cout << error;
        exit(1);
    }
    catch (...) {
        cout << "Unknown error" << endl;
        exit(1);
    }
}

void RinexParser::getCoordinates(char *filenameOut, char *filenameTimeOut) {
    string extension = getFileExtension(this->filename);
    if(extension.find('n') < extension.length()) {
        throw std::runtime_error("Expected Navigation Rinex file, but got another!");
    }

    Rinex3NavHeader header;
    Rinex3NavData data;
    Rinex3NavStream navFile(this->filename);
    navFile.exceptions(ios::failbit);

    cout << "Reading " << this->filename << endl;

    navFile >> header;
    header.dump(cout);

    Rinex3NavStream navOut(filenameOut, ios::app);
    Rinex3NavStream timeOut(filenameTimeOut, ios::out|ios::trunc);

    while (navFile >> data) {
        RinexSatID PRNSat(this->PRNCode, SatelliteSystem::GPS);

        if (data.sat == PRNSat) {
            CivilTime civilTime(data.time);

            navOut << data.px << " " << data.py << " " << data.pz << endl;
            timeOut << civilTime << endl;
        }
    }

    navOut.close();
}

tuple<string, vector<double>> RinexParser::getAntennaPosition(void) {
    Rinex3ObsHeader header;
    Rinex3ObsStream obsFile(this->filename);
    obsFile.exceptions(ios::failbit);

    obsFile >> header;

    // Save antenna position from header in vector type.
    vector<double> antennaPosition = {
            header.antennaPosition[0],
            header.antennaPosition[1],
            header.antennaPosition[2]
    };

    obsFile.close();

    return make_tuple(header.markerName, antennaPosition);
}

map<int, long double> RinexParser::getObservation(const string &obsCode) {
    string extension = getFileExtension(this->filename);
    if(extension.find('o') < extension.length()) {
        throw std::runtime_error("Expected Observation Rinex file, but got another!");
    }

    map<int, long double> timedObs = {};

    try {
        Rinex3ObsHeader header;
        Rinex3ObsData data;
        RinexDatum dataObject;
        Rinex3ObsStream obsFile(this->filename);
        obsFile.exceptions(ios::failbit);

        cout << "Reading " << this->filename << endl;

        obsFile >> header;
        header.dump(cout);

        Rinex3ObsStream antennaOut("antennaPosition", ios::out | ios::app);

        antennaOut << header.markerName << endl;
        antennaOut << setprecision(13) << header.antennaPosition << endl;

        while (obsFile >> data) {
            CivilTime civilTime(data.time);

            RinexSatID satId(this->PRNCode, SatelliteSystem::GPS);
            auto pointer = data.obs.find(satId);

            if (pointer == data.obs.end()) {
                cout << "PRN " << satId << " not in view." << endl;
            } else {
                int timeInSec = int(civilTime.convertToCommonTime().getSecondOfDay());

                dataObject = data.getObs(satId, obsCode, header);
                timedObs[timeInSec] = dataObject.data;
            }
        }

        cout << "Read " << obsFile.recordNumber << " epochs." << endl;

        obsFile.close();

        return timedObs;
    }
    catch(FFStreamError& error) {
        cout << error;
        exit(1);
    }
    catch(Exception& error) {
        cout << error;
        exit(1);
    }
    catch (...) {
        cout << "Unknown error" << endl;
        exit(1);
    }
}

void RinexParser::getObservation(const string &filenameOut, const string &filenameTimeOut, const string &obsCode) {
    string extension = getFileExtension(this->filename);
    if(extension.find('o') < extension.length()) {
        throw std::runtime_error("Expected Observation Rinex file, but got another!");
    }

    try {
        Rinex3ObsHeader header;
        Rinex3ObsData data;
        RinexDatum dataObject;
        Rinex3ObsStream obsFile(this->filename);
        obsFile.exceptions(ios::failbit);

        cout << "Reading " << this->filename << endl;

        obsFile >> header;
        header.dump(cout);

        Rinex3ObsStream antennaOut("antennaPosition", ios::out | ios::app);
        antennaOut << header.markerName << endl;
        antennaOut << setprecision(13) << header.antennaPosition << endl;

        Rinex3ObsStream rout(filenameOut, ios::out|ios::app);
        Rinex3ObsStream time_out(filenameTimeOut, ios::out|ios::app);

        while (obsFile >> data) {
            CivilTime civilTime(data.time);
            cout << int(civilTime.convertToCommonTime().getSecondOfDay()) << endl;

            RinexSatID satId(this->PRNCode, SatelliteSystem::GPS);
            Rinex3ObsData::DataMap::iterator pointer = data.obs.find(satId);

            if (pointer == data.obs.end()) {
                cout << "PRN " << satId << " not in view." << endl;
            } else {
                time_out << civilTime << endl;
                dataObject = data.getObs(satId, obsCode, header);

                rout << setprecision(13) << dataObject.data << endl;
            }
        }

        // Close all files
        rout.close();
        antennaOut.close();
        time_out.close();
        obsFile.close();

        cout << "Read " << obsFile.recordNumber << " epochs." << endl;
    }
    catch(FFStreamError& error) {
        cout << error;
        exit(1);
    }
    catch(Exception& error) {
        cout << error;
        exit(1);
    }
    catch (...) {
        cout << "Unknown error" << endl;
        exit(1);
    }
}

void RinexParser::getFirstDifferences(RinexParser secondSatObs, const string &filenameOut, const string &obsCode) {
    string extension = getFileExtension(this->filename);
    if(extension.find('o') < extension.length()) {
        throw std::runtime_error("Expected Observation Rinex file, but got another!");
    }

    // Observations files from two difference stations
    auto firstSat = this->getObservation(obsCode);
    auto secondSat = secondSatObs.getObservation(obsCode);

    // Output file with first differences
    ofstream diffFile;
    diffFile.open(filenameOut.c_str(), ios::out);

    for (auto const& x : firstSat) {
        auto obs = secondSat.find(x.first);

        if (obs != secondSat.end()) {
            // First differences and time
            diffFile << setprecision(13) << x.second - obs->second << "|" << x.first << endl;
        }
    }

    diffFile.close();
}
