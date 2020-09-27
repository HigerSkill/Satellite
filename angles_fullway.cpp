#include <iostream>
#include <string>
#include <vector>

#include "parsers/rinex.cpp"
#include "parsers/sp3.cpp"


int get_angles_and_coords(
        const std::string& rinex_file, char *sp3_file, int prn) {
    /* Rinex and SP3 files must be for one day. */

    // Get antenna position
    string antenna_name;
    vector<double> antenna_position;

    tie(antenna_name, antenna_position) =
            get_antenna_position(rinex_file);

    Position station (
            antenna_position[0],
            antenna_position[1],
            antenna_position[2]);
    cout << station << endl;
    // Get time when antenna receive signal from satellite
    vector<int> time_obs = get_time_obs(rinex_file, prn);

    // Get coordinates satellite and time from SP3 file
    map<int, vector<double>> coordinates_time = get_coordinates(sp3_file, prn);

    // Save coords from SP3 to file
    ofstream coords_file;
    ofstream time_coords_file;
    coords_file.open(
            antenna_name + "_coords", ios::out|ios::trunc);
    time_coords_file.open(
            antenna_name + "_time_coords", ios::out|ios::trunc);

    auto it = coordinates_time.begin();
    for (int i = 0; it != coordinates_time.end(); it++, i++) {
        // If time from time_obs not found in coordinates_time,
        // then we'll delete it
        coords_file <<
        it->second[0] << " " <<  it->second[1] << " " << it->second[2] << endl;
        time_coords_file << it->first << endl;
    }

    // Filter coordinates_time by time_obs
    it = coordinates_time.begin();
    for (int i = 0; it != coordinates_time.end(); it++, i++) {
        // If time from time_obs not found in coordinates_time,
        // then we'll delete it
        if (find(time_obs.begin(), time_obs.end(), it->first) == time_obs.end()) {
            coordinates_time.erase(it->first);
        }
    }

    // Initialize and clear files for angles and time
    ofstream time_file;
    ofstream angles_file;
    time_file.open(antenna_name + "_time", ios::out|ios::trunc);
    angles_file.open(antenna_name + "_angles", ios::out|ios::trunc);

    // Get angles between satellite and station and save to files
    map<int, double> angle_time;
    it = coordinates_time.begin();
    for (int i = 0; it != coordinates_time.end(); it++, i++) {
        // Set position x, y, z
        Position satellite (
                it->second[0], it->second[1], it->second[2]);

        // Save angle between satellite and station for every time stamp
        double angle = satellite_station_angle(satellite, station);
        angle_time[it->first] = angle;

        // Write angles and time to files
        time_file << it->first << endl;
        angles_file << angle << endl;
    }

    return 0;
}
