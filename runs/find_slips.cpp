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
    string sp3Name = "igs";
    string sp3Ext = ".sp3";

    string rinexName = "badg"; // Set up your antenna name
    string rinexExt = ".20o"; // Year

    int week = 2112; // GPS Week and day can be calculated on http://navigationservices.agi.com/GNSSWeb/
    int day = 4;

    // From 1 day to 366
    for (int i = 184; i <= 366; i++) {
        cout << "Day: " << i << endl;

        string iStr = to_string(i);
        string rinexDay;

        if (i < 10) rinexDay = "00" + iStr + "0";
        if (10 <= i  &&  i < 100) rinexDay = "0" + iStr + "0";
        if (100 <= i) rinexDay = iStr + "0";

        string rinexFile = rinexName + rinexDay + rinexExt;
        string sp3File = sp3Name + to_string(week) + to_string(day) + sp3Ext;

        cout << sp3File << endl;

        if (day == 6) {
            week++;
        }

        day++;
        day = day % 7;

        // Station configuration
//        ConfigRun config{
//                0,
//                "L1C",
//                56.021,
//                37.215,
//                2845456.3,
//                2160954.37,
//                5265993.4
//        }; // MDVJ
//
//        ConfigRun config{
//                0,
//                "L1C",
//                14.535, 121.041,
//                3664939.7992, 1409154.0345, 5009571.3524
//        }; // JOZE

//        ConfigRun config{
//                0,
//                "L1C",
//                14.535, 121.041,
//                -3184365.6327, 5291038.8848, 1590414.0821
//        }; // PTGG

//        ConfigRun config{
//                0,
//                "L1C",
//                52.277, 17.073,
//                3738358.833, 1148173.963, 5021816.113
//        }; // BOR1
//
        ConfigRun config{
                0,
                "L1C",
                51.770, 102.235,
                -838281.513, 3865777.334, 4987624.632
        }; // BADG

        string sp3Path = "/Users/aleksandrdimov/Documents/master/satellite/output/sp3/2020/" + sp3File; // Path to SP3 files
        char * sp3PathCh = new char [sp3Path.length()+1];
        strcpy(sp3PathCh, sp3Path.c_str());

        string rinexPath = "/Users/aleksandrdimov/Documents/master/satellite/output/rinex/2020/badg/" + rinexFile; // Path to Rinex files
        char * rinexPathCh = new char [rinexPath.length()+1];
        strcpy(rinexPathCh, rinexPath.c_str());

        string outFile = "../output/badg/" + rinexDay + ".txt";
        char * outPathCh = new char [outFile.length()+1];
        strcpy(outPathCh, outFile.c_str());

        config.sp3_file = sp3PathCh;
        config.rinex_file_first = rinexPathCh;
        config.fileOutSlipsProjections = outPathCh;

        for (int prn = 1; prn <= 26; prn++) {
            cout << prn << endl;

            config.PRNCode = prn;
            RinexObs rinex(config.rinex_file_first, config.PRNCode, SatelliteSystem::GPS);

            getSlipsMAProjections(rinex, config);
        }

        delete[] sp3PathCh;
        delete[] rinexPathCh;
        delete[] outPathCh;
    }
}