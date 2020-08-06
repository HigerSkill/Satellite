#include <iostream>
#include <string>
#include <vector>

#include "Rinex3NavStream.hpp"
#include "Rinex3NavHeader.hpp"
#include "Rinex3NavData.hpp"

#include "Rinex3ObsData.hpp"
#include "Rinex3ObsHeader.hpp"
#include "Rinex3ObsStream.hpp"

#include "TimeString.hpp"
#include <string>

using namespace std;
using namespace gpstk;

int obs_parser_file(const string& filename, const string& filename_out, const string& obs_code, int prn) {
    /* Parse Rinex observation file and write time and data by code in files.
     *
     * Arguments:
     *  filename (string): Name of rinex observation file.
     *  filename_out (string): Name of out file where will be data by code.
     *  obs_code (string): Observation code (C1C - pseudorange, L1C - Carrier Phase and etc., see docs rinex format).
     *  prn (int): The PRN of the satellite.
     * */
    try {
        cout << "Reading " << filename << endl;

        Rinex3ObsStream obs_file(filename);
        obs_file.exceptions(ios::failbit);

        Rinex3ObsHeader header;
        Rinex3ObsData data;
        RinexDatum data_object;

        obs_file >> header;
        header.dump(cout);

        Rinex3ObsStream antenna_out("antenna_position", ios::out|ios::app);
        antenna_out << header.markerName << endl;
        antenna_out << std::setprecision(13) << header.antennaPosition << endl;

        Rinex3ObsStream rout(filename_out, ios::out|ios::app);

        size_t ext = filename_out.find_last_of('.');
        string time_filename_out = filename_out.substr(0, ext) + "_time";
        cout << time_filename_out;
        Rinex3ObsStream time_out(time_filename_out, ios::out|ios::app);

        while (obs_file >> data) {
            CivilTime civtime(data.time);
            cout << int(civtime.convertToCommonTime().getSecondOfDay()) << endl;

            RinexSatID prn_sat(prn, SatID::systemGlonass);
            Rinex3ObsData::DataMap::iterator pointer = data.obs.find(prn_sat);

            if (pointer == data.obs.end()) {
                cout << "PRN " << prn_sat << " not in view." << endl;
            } else {
                time_out << civtime << std::endl;
                data_object = data.getObs(prn_sat, obs_code, header);

                long double obs_data = data_object.data;
                rout << std::setprecision(13) << obs_data << std::endl;
            }
        }
        rout << "Gluing" << std::endl;

        // Close all files
        rout.close();
        antenna_out.close();
        time_out.close();
        obs_file.close();

        cout << "Read " << obs_file.recordNumber << " epochs."  << endl;

        return 0;
    }
    catch(FFStreamError& error) {
        cout << error;
        return 0;
//        exit(1);
    }
    catch(Exception& error) {
        cout << error;
        return 0;
//        exit(1);
    }
    catch (...) {
        cout << "Unknown error" << endl;
        return 0;
//        exit(1);
    }
}

map<int, long double> obs_parser(const string& filename, const string& obs_code, int prn) {
    /* Return time and data by code from Rinex observation file.
     *
     * Arguments:
     *  filename (string): Name of rinex observation file.
     *  obs_code (string): Observation code (C1C - pseudorange, L1C - Carrier Phase and etc., see docs rinex format).
     *  prn (int): The PRN of the satellite.
     * */
    map<int, long double> timed_obs = {};

    try {
        cout << "Reading " << filename << endl;

        Rinex3ObsStream obs_file(filename);
        obs_file.exceptions(ios::failbit);

        Rinex3ObsHeader header;
        Rinex3ObsData data;
        RinexDatum data_object;

        obs_file >> header;
        header.dump(cout);

        Rinex3ObsStream antenna_out("antenna_position", ios::out | ios::app);
        antenna_out << header.markerName << endl;
        antenna_out << std::setprecision(13) << header.antennaPosition << endl;

        while (obs_file >> data) {
            CivilTime civtime(data.time);
//            cout << int(civtime.convertToCommonTime().getSecondOfDay()) << endl;

            RinexSatID prn_sat(prn, SatID::systemGlonass);
            Rinex3ObsData::DataMap::iterator pointer = data.obs.find(prn_sat);

            if (pointer == data.obs.end()) {
                int a = 0;
//                cout << "PRN " << prn_sat << " not in view." << endl;
            } else {
                int time_in_sec = int(civtime.convertToCommonTime().getSecondOfDay());
                data_object = data.getObs(prn_sat, obs_code, header);

                long double obs_data = data_object.data;

                timed_obs[time_in_sec] = obs_data;
            }
        }

        cout << "Read " << obs_file.recordNumber << " epochs." << endl;

        return timed_obs;
    }
    catch(FFStreamError& error) {
        cout << error;
        return timed_obs;
//        exit(1);
    }
    catch(Exception& error) {
        cout << error;
        return timed_obs;
//        exit(1);
    }
    catch (...) {
        cout << "Unknown error" << endl;
        return timed_obs;
//        exit(1);
    }
}

int nav_parser(const char *filename, const char *filename_out, int prn) {
    /* Parse Rinex navigation file and write time and coordinates in files.
     *
     * Arguments:
     *  filename (string): Name of rinex navigation file.
     *  filename_out (string): Name of out file where will be data.
     *  prn (int): The PRN of the satellite.
     * */
    cout << "Reading " << filename << endl;

    Rinex3NavStream nav_file(filename);
    nav_file.exceptions(ios::failbit);

    Rinex3NavHeader header;
    Rinex3NavData data;

    nav_file >> header;
    header.dump(cout);

    Rinex3NavStream nav_out(filename_out, std::ios::app);

    string out_file = filename_out;
    size_t ext = out_file.find_last_of('.');
    string time_filename_out = out_file.substr(0, ext) + "_time" + out_file.substr(1, ext);
    Rinex3NavStream time_out(time_filename_out.c_str(), ios::out|ios::trunc);

    while (nav_file >> data) {
        RinexSatID prn_sat(prn, SatID::systemGPS);

        if (data.sat == prn_sat) {
            CivilTime civtime(data.time);

            nav_out << data.px << " " << data.py << " " << data.pz << endl;
            time_out << civtime << endl;
        }
    }
    return 0;
}


