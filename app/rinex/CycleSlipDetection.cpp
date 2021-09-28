#include "CycleSlipDetection.h"

#include <cmath>
#include <numeric>
#include <list>


#include "MovingAverage.h"

using namespace std;

CycleSlipDetection::CycleSlipDetection(RinexObs &firstStation, RinexObs &secondStation)
        : firstStation(firstStation), secondStation(secondStation) {
}



vector<int> CycleSlipDetection::findObviousSlips(const std::string &obsCode) {
    vector<double> single_diffs;
    vector<int> timestamps;
    vector<int> cycle_slips;

    tie(timestamps, single_diffs) = firstStation.getSingleDifferences(secondStation, obsCode);

    double sum = accumulate(single_diffs.begin(), single_diffs.end(), 0.0);
    double mean = sum / single_diffs.size();

    double sqsSum = inner_product(single_diffs.begin(), single_diffs.end(), single_diffs.begin(), 0.0);
    double stDev = std::sqrt(sqsSum / single_diffs.size() - mean * mean);

    // Set upper and lower limit to 3 standard deviation
    double anomaly_cut_off = stDev * 3;
    double lower_limit  = mean - anomaly_cut_off;
    double upper_limit = mean + anomaly_cut_off;

    // Generate outliers
    int i = 0;
    for (double outlier : single_diffs) {
        if (outlier > upper_limit || outlier < lower_limit) {
            cycle_slips.push_back(timestamps[i]);
            i++;
        }
    }

    return cycle_slips;
}

std::vector<int> CycleSlipDetection::findMovingAverageSlips(const string &obsCode) {
    map<int, long double> phase_measures = this->firstStation.getObservation(obsCode);

    vector<int> slips;

    MovingAverage ma(5);

    for (auto const& pm : phase_measures) {
        double time = pm.first;
        double measure = pm.second;

        ma.add(measure);

        setprecision(13);
        if (measure > 1.5*ma.avg()) {
            slips.push_back(time);
        }
    }

    return slips;
}
