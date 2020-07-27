#include <iostream>
#include <string>
#include <vector>

using namespace std;

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