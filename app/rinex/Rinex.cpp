#include "Rinex.h"

#include "../utils/Files.h"

#include <Rinex3ObsStream.hpp>
#include <Rinex3ObsData.hpp>
#include <Rinex3NavStream.hpp>
#include <Rinex3NavData.hpp>


using namespace gpstk, std;

Rinex::Rinex(char *filename, int PRNCode) {
    string extension = getFileExtension(this->filename);

    if(extension.find('o') < 1) {
        throw std::runtime_error("Expected Observation Rinex file, but got another!");
    }

    this->filename = filename;
    this->PRNCode = PRNCode;


}

bool Rinex::PRNCodeExists(const std::string& obsCode) {
    try {
        Rinex3ObsHeader header;
        Rinex3ObsData data;
        RinexDatum dataObject;

        Rinex3ObsStream obsFile(this->filename);
        obsFile.exceptions(ios::failbit);

        obsFile >> header;

        while (obsFile >> data) {
            RinexSatID satId(this->PRNCode, SatelliteSystem::GPS);
            Rinex3ObsData::DataMap::iterator pointer = data.obs.find(satId);

            if (pointer == data.obs.end())
                return false;


            return true;
        }

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

string Rinex::getAntennaName(void) {
    Rinex3ObsHeader header;
    Rinex3ObsStream obsFile(this->filename);
    obsFile.exceptions(ios::failbit);

    obsFile >> header;
    obsFile.close();

    return header.markerName;
}



