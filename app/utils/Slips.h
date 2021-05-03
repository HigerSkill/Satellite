#ifndef SATELLITE_SLIPS_H
#define SATELLITE_SLIPS_H

#include "../rinex/RinexObs.h"
#include "../rinex/CycleSlipDetection.h"
#include "../sp3/SP3.h"
#include "../sp3/Projection.h"
#include "Structs.h"

#include <vector>


using namespace std;
using namespace gpstk;

/*
 * Allows you to find projections of satellite coordinates at the time of Cycle Slips
 *
 * @param config Stores the path to rinex/sp3 files, prn, observation code and etc.
 */
void getSlipsMAProjections(RinexObs &rinex, ConfigRun config) {

    CycleSlipDetection slips(rinex, rinex);
    vector<int> slipsTime = slips.findMovingAverageSlips(config.obsCode);

    SP3 sp3(config.sp3_file, config.PRNCode, 10, SatelliteSystem::Glonass);

    ofstream slipsOut(config.fileOutSlipsProjections, ios::app | ios::out);

    if (!slipsTime.empty()) {
        slipsOut << config.PRNCode << endl;
        slipsOut.close();

        Projection slipsProjections(sp3, config.station);
        slipsProjections.getProjections(config.fileOutSlipsProjections, slipsTime);
    }
}


#endif //SATELLITE_SLIPS_H
