#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct sat_info {
    int prn;
    string code;
    double wavelength;
};

int first_differences_file(const string& observations_filename, const string& first_differences_filename) {
    /* Calculate and write first differences for observations in file. */

    ifstream obs_file;
    obs_file.open(observations_filename.c_str(), ios::in);

    ofstream diff_file;
    diff_file.open(first_differences_filename.c_str(), ios::out);

    double obs;
    vector<double> observations;
    while (obs_file >> obs) {
        observations.push_back(obs);
    }

    for (int i=0; i < floor(observations.size() / 2); ++i) {
        diff_file << setprecision(13) << observations[i] - observations[i+1] << endl;
    }

    return 0;
}

int differences(
        const string& first_sat_obs_file,
        const string& second_sat_obs_file,
        const string& differences_file,
        const sat_info& satellite={18, "L1C", 1}) {
    /* Calculate and write first or second (if lambda > 0) differences for observations in file. */

    // Observations files
    auto first_sat = obs_parser(first_sat_obs_file, satellite.code, satellite.prn);
    auto second_sat = obs_parser(second_sat_obs_file, satellite.code, satellite.prn);

    // Output file with first or second differences
    ofstream diff_file;
    diff_file.open(differences_file.c_str(), ios::out);

    for (auto const& x : first_sat) {
        auto obs = second_sat.find(x.first);

        if (obs != second_sat.end()) {
            cout << setprecision(13) << x.second - obs->second << endl;
            diff_file << setprecision(13) << x.second - obs->second << "|" << x.first << endl;
        }
    }
}