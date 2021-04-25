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

    string rinexName = "ptbb"; // Set up your antenna name
    string rinexExt = ".20o"; // Year

    int week = 2086; // GPS Week and day can be calculated on http://navigationservices.agi.com/GNSSWeb/
    int day = 3;

    // From 1 day to 366
    for (int i = 1; i <= 366; i++) {
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
        ConfigRun config{0, "L1C", 52.296, 10.460, 3844060.11,  709661.2, 5023129.46};

        string sp3Path = "/home/alex/Downloads/sp3/" + sp3File; // Path to SP3 files
        char * sp3PathCh = new char [sp3Path.length()+1];
        strcpy(sp3PathCh, sp3Path.c_str());

        string rinexPath = "/home/alex/Downloads/ptbb_2020/" + rinexFile; // Path to Rinex files
        char * rinexPathCh = new char [rinexPath.length()+1];
        strcpy(rinexPathCh, rinexPath.c_str());

        string outFile = "../output/20/" + rinexDay + ".txt";
        char * outPathCh = new char [outFile.length()+1];
        strcpy(outPathCh, outFile.c_str());

        config.sp3_file = sp3PathCh;
        config.rinex_file_first = rinexPathCh;
        config.fileOutSlipsProjections = outPathCh;

        for (int prn = 1; prn <= 32; prn++) {
            cout << prn << endl;

            config.PRNCode = prn;
            RinexObs rinex(config.rinex_file_first, config.PRNCode);

            getSlipsMAProjections(rinex, config);
        }

        delete[] sp3PathCh;
        delete[] rinexPathCh;
        delete[] outPathCh;
    }
}