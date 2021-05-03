#ifndef SATELLITE_RINEXOBS_H
#define SATELLITE_RINEXOBS_H

#include <string>

#include <Rinex3ObsStream.hpp>
#include <Rinex3ObsData.hpp>
#include <Rinex3NavStream.hpp>


/**
 * Provides the ability to receive information stored for the specified (by PRN code) satellite.
 */
class RinexObs {
private:
    void resetFile();

public:
    char *filename;
    int PRNCode;

    gpstk::SatelliteSystem system;
    gpstk::Rinex3ObsHeader header;
    gpstk::Rinex3ObsStream obsFile;

    /**
     * Constructor create RinexParser object.
     *
     * @param filename Path to RinexObs the file.
     * @param PRNCode PRN code of the satellite.
     */
    RinexObs(char* filename, int PRNCode, gpstk::SatelliteSystem system=gpstk::SatelliteSystem::GPS);

    RinexObs(const RinexObs& rinexObs);


    /**
     * Destructor RinexParser object.
     */
    ~RinexObs();

    /**
     * Check that `PRN` code exists for the observation code (L1, L2 and etc.)
     *
     * @param obsCode Path to RinexObs the file.
     *
     * @return Does the PRN code exist or not
     */
    bool PRNCodeExists(const std::string& obsCode);

    /**
     * Get antenna name from a rinex file.
     *
     *  @return Name of the satellite and position.
     */
    std::string getAntennaName();

    /**
     * Get antenna position from a rinex file.
     *
     *  @return Tuple of name of satellite and position.
     */
    std::tuple<std::string, std::vector<double>>getAntennaPosition();

    /**
     * Parse time when antenna receive signal from satellite.
     *
     * @return vector of time when antenna receive signal from satellite.
     */
    std::vector<int> getTimeObs();

    /**
     * Get antenna position from a rinex file.
     *
     *  @param obsCode Observation code (C1C - pseudorange, L1C - Carrier Phase and etc., see docs rinex format).
     *
     *  @return Map time and data for selected obsCode.
     */
    std::map<int, long double> getObservation(const std::string& obsCode);

    /**
     * Parse Rinex observation file and write time and data by code in files.
     *
     *  @param filenameOut Path to output file with observations.
     *  @param obsCode Observation code (C1C - pseudorange, L1C - Carrier Phase and etc., see docs rinex format).
     */
    void getObservation(const std::string& filenameOut, const std::string& obsCode);

    /**
     * Calculate and write single differences for observations in file.
     *
     *  @param secondSatObs RinexParser instance of second observations.
     *  @param filenameOut Name of output file where output data is store.
     *  @param obsCode Observation code (C1C - pseudorange, L1C - Carrier Phase and etc., see docs rinex format).
     */
    void getSingleDifferences(RinexObs secondSatObs, const std::string& filenameOut, const std::string& obsCode);

    /**
     * Calculate single differences for observations.
     *
     *  @param secondSatObs RinexParser instance of second observations.
     *  @param filenameOut Name of output file where output data is store.
     *  @param obsCode Observation code (C1C - pseudorange, L1C - Carrier Phase and etc., see docs rinex format).
     *
     *  @return Tuple of the time and single differences.
     */
    std::tuple<std::vector<int>, std::vector<double>> getSingleDifferences(
            RinexObs secondSatObs, const std::string& obsCode);


};


#endif //SATELLITE_RINEXOBS_H
