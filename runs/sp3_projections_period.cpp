#include <iostream>

#include "../app/rinex/RinexObs.h"
#include "../app/sp3/SP3.h"

#include "../app/rinex/CycleSlipDetection.h"
#include "../app/sp3/Projection.h"
#include "../app/utils/Slips.h"
#include "../app/utils/Structs.h"
#include "../app/rinex/MovingAverage.h"

#include <cstring>

#include <SP3EphemerisStore.hpp>
#include <CivilTime.hpp>
#include <Position.hpp>

using namespace std;
using namespace gpstk;

int main() {
    string sp3Name = "igl";
    string sp3Ext = ".sp3";

    int week = 2086; // GPS Week and day can be calculated on http://navigationservices.agi.com/GNSSWeb/
    int day = 3;

    // From 1 day to 366
    for (int i = 1; i <= 365; i++) {
        cout << "Day: " << i << endl;

        string iStr = to_string(i);

        string sp3File = sp3Name + to_string(week) + to_string(day) + sp3Ext;

        cout << sp3File << endl;

        if (day == 6) {
            week++;
        }

        day++;
        day = day % 7;

        // Station configuration
//        ConfigRun config{
//                1,
//                "L1C",
//                32.77,
//                35.020,
//                4396111.1752,
//                3080477.641910,
//                3433499.46187
//        }; // BSHM

//        ConfigRun config{
//                2,
//                "L1C",
//                56.838,
//                60.615,
//                1716013.966,
//                3047281.697,
//                316302.551
//        }; // URAL

        ConfigRun config{
                10,
                "L1C",
                14.535, 121.041
                3664939.7992, 1409154.0345, 5009571.3524
        }; // JOZE


//        ConfigRun config{
//                26,
//                "L1C",
//                51.770,
//                102.235,
//                -838281.513,
//                3865777.334,
//                4987624.632
//        }; // BADG

        string sp3Path = "/Users/aleksandrdimov/Documents/master/satellite/output/sp3/2020" + sp3File; // Path to SP3 files
        char *sp3PathCh = new char[sp3Path.length() + 1];
        strcpy(sp3PathCh, sp3Path.c_str());

        config.sp3_file = sp3PathCh;

        SP3 sp3(sp3PathCh, config.PRNCode, 10, SatelliteSystem::Glonass);
        Projection projections(sp3, config.station);

        string filename =  "../output/joze/projection_";
        filename = filename + to_string(config.PRNCode) + ".txt";

        char file_out[filename.length() + 1];
        strcpy(file_out, filename.c_str());

        projections.getProjections(file_out);

        delete[] sp3PathCh;
    }
}