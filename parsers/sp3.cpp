#include <iostream>

#include <SP3Stream.hpp>
#include <SP3Data.hpp>
#include <CivilTime.hpp>

using namespace std;
using namespace gpstk;

int coordinates_in_file(char* filename, char* filename_out, int prn) {
    /* Parse sp3 file and write time and coordinates in files.
     * Get the three-vector for position | velocity (m | dm/s).
     *
     * Arguments:
     *  filename (string): Name of sp3 file.
     *  filename_out (string): Name of out file where will be data.
     *  prn (int): The PRN of the satellite.
     * */
    SP3Stream sp3_file(filename);

    SP3Stream rout(filename_out, ios::out|ios::trunc);

    string out_file = filename_out;
    size_t ext = out_file.find_last_of('.');
    string time_filename_out = out_file.substr(0, ext) + "_time" + out_file.substr(1, ext);
    SP3Stream time_out(time_filename_out.c_str(), ios::out|ios::trunc);

    SP3Header header;
    sp3_file >> header;
    rout.header = sp3_file.header;

    SP3Data data;
    SP3SatID prn_sat(prn, prn_sat.systemGlonass);

    while (sp3_file >> data) {
        if (data.sat == prn_sat) {
            CivilTime civtime(data.time);

            rout << data.x[0] << "," << data.x[1] << "," << data.x[2] << endl;
            time_out << civtime << endl;
        }
    }
    return 0;
}