#include "RinexObs.h"

#include "../utils/Files.h"


using namespace gpstk;
using namespace std;

RinexObs::RinexObs(char *filename, int PRNCode, SatelliteSystem system) {
    string extension = getFileExtension(filename);

    if(extension.find('o') < 1) {
        throw std::runtime_error("Expected Observation RinexObs file, but got another!");
    }

    this->filename = filename;
    this->PRNCode = PRNCode;
    this->system = system;

}

RinexObs::RinexObs(const RinexObs &rinexObs) {
    this->filename = rinexObs.filename;
    this->PRNCode = rinexObs.PRNCode;
    this->system = rinexObs.system;
}


bool RinexObs::PRNCodeExists(const std::string& obsCode) {
    try {
        Rinex3ObsData data;

        Rinex3ObsHeader header;
        Rinex3ObsStream obsFile;

        obsFile.open(filename, ios::in);
        obsFile.exceptions(ios::failbit);
        obsFile >> header;

        while (obsFile >> data) {
            RinexSatID satId(PRNCode, system);

            if (data.obs.find(satId) == data.obs.end())
                return false;

            return true;
        }
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

string RinexObs::getAntennaName() {
    Rinex3ObsHeader header;
    Rinex3ObsStream obsFile;

    obsFile.open(filename, ios::in);
    obsFile.exceptions(ios::failbit);
    obsFile >> header;

    return header.markerName;
}


tuple<string, vector<double>> RinexObs::getAntennaPosition() {
    // Save antenna position from header in vector.
    Rinex3ObsHeader header;
    Rinex3ObsStream obsFile;

    obsFile.open(filename, ios::in);
    obsFile.exceptions(ios::failbit);
    obsFile >> header;

    vector<double> antennaPosition = {
            header.antennaPosition[0],
            header.antennaPosition[1],
            header.antennaPosition[2]
    };

    return make_tuple(header.markerName, antennaPosition);
}


vector<int> RinexObs::getTimeObs() {
    try {
        Rinex3ObsData data;

        vector<int> time;

        Rinex3ObsHeader header;
        Rinex3ObsStream obsFile;

        obsFile.open(this->filename, ios::in);
        obsFile.exceptions(ios::failbit);
        obsFile >> header;

        while (obsFile >> data) {
            CivilTime obsTime(data.time);
            RinexSatID satId(PRNCode, system);

            auto pointer = data.obs.find(satId);

            if (pointer == data.obs.end()) {
                cout << "PRN " << satId << " not in view." << endl;
            } else {
                time.push_back(int(obsTime.convertToCommonTime().getSecondOfDay()));
            }
        }

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

map<int, long double> RinexObs::getObservation(const string &obsCode) {
    map<int, long double> timedObs = {};

    Rinex3ObsHeader header;
    Rinex3ObsStream obsFile;

    obsFile.open(filename, ios::in);
    obsFile.exceptions(ios::failbit);
    obsFile >> header;

    try {
        Rinex3ObsData data;
        RinexDatum datum;

        cout << "Reading " << filename << endl;

        while (obsFile >> data) {
            CivilTime civilTime(data.time);

            RinexSatID satId(PRNCode, system);
            auto pointer = data.obs.find(satId);

            if (pointer == data.obs.end()) {
                continue;
            } else {
                int timeInSec = int(civilTime.convertToCommonTime().getSecondOfDay());

                datum = data.getObs(satId, obsCode, header);
                timedObs[timeInSec] = datum.data;
            }
        }

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

void RinexObs::getObservation(const string &filenameOut, const string &obsCode) {
    try {
        Rinex3ObsData data;
        RinexDatum datum;

        cout << "Reading " << filename << endl;

        Rinex3ObsHeader header;
        Rinex3ObsStream obsFile;

        obsFile.open(filename, ios::in);
        obsFile.exceptions(ios::failbit);
        obsFile >> header;

        Rinex3ObsStream rout(filenameOut, ios::out);

        while (obsFile >> data) {
            CivilTime civilTime(data.time);

            RinexSatID satId(PRNCode, system);
            Rinex3ObsData::DataMap::iterator pointer = data.obs.find(satId);

            if (pointer == data.obs.end()) {
                continue;
            } else {
                int timeInSec = int(civilTime.convertToCommonTime().getSecondOfDay());
                datum = data.getObs(satId, obsCode, header);

                rout << setprecision(13) << timeInSec << "," << datum.data << endl;
            }
        }

        // Close out file
        rout.close();
        obsFile.close();
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

void RinexObs::getSingleDifferences(RinexObs secondSatObs, const string &filenameOut, const string &obsCode) {
    // Observations files from two difference stations
    auto firstSat = this->getObservation(obsCode);
    auto secondSat = secondSatObs.getObservation(obsCode);

    // Output file with single differences
    ofstream diffFile;
    diffFile.open(filenameOut.c_str(), ios::out);

    for (auto const& x : firstSat) {
        auto obs = secondSat.find(x.first);

        if (obs != secondSat.end()) {
            diffFile << setprecision(13) << x.first << "," << x.second - obs->second << endl;
        }
    }

    diffFile.close();
}

tuple<vector<int>, vector<double>> RinexObs::getSingleDifferences(RinexObs secondSatObs, const string &obsCode) {
    // Observations files from two difference stations
    auto firstSat = this->getObservation(obsCode);
    auto secondSat = secondSatObs.getObservation(obsCode);

    vector<double> singles;
    vector<int> timestamps;

    for (auto const& x : firstSat) {
        auto obs = secondSat.find(x.first);

        if (obs != secondSat.end()) {
            singles.push_back(x.second - obs->second);
            timestamps.push_back(x.first);
        }
    }

    return make_tuple(timestamps, singles);
}
