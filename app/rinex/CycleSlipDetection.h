#ifndef SATELLITE_CYCLESLIPDETECTION_H
#define SATELLITE_CYCLESLIPDETECTION_H

#include "RinexObs.h"

class CycleSlipDetection {
private:
    RinexObs &firstStation;
    RinexObs &secondStation;

public:
    /**
     * Constructor create CycleSlipDetection object.
     *
     * @param firstStation Instance rinex parser of first station.
     * @param secondStation Instance rinex parser of second station.
     */
    CycleSlipDetection(RinexObs &firstStation, RinexObs &secondStation);

    /**
     * Constructor create CycleSlipDetection object for only one RinexObs.
     *
     * @param firstStation Instance rinex parser of first station.
     */
    CycleSlipDetection(RinexObs &station);

    /**
     * Find obvious Cycle Slips in single differences.
     *
     * @param obsCode Observation Code.
     *
     * @return Vector of timestamps of the obvious slips.
     */
    std::vector<int> findObviousSlips(const std::string &obsCode);

    /**
     * Find obvious Cycle Slips in single differences based on moving average.
     *
     * @param obsCode Observation Code.
     *
     * @return Vector of timestamps of the moving average slips.
     */
    std::vector<int> findMovingAverageSlips(const std::string &obsCode);

    /**
     * Find obvious Cycle Slips in single differences based on moving average.
     *
     * @param obsCode Observation Code.
     *
     * @return Vector of timestamps of the moving average slips.
     */
    std::vector<int> findMASlips(const std::string &obsCode);


};


#endif //SATELLITE_CYCLESLIPDETECTION_H
