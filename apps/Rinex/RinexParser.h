#ifndef SATELLITE_RINEXPARSER_H
#define SATELLITE_RINEXPARSER_H

#include <string>
#include <vector>
#include <map>

/// Class RinexParser provides the ability to receive information stored for the specified satellite.
class RinexParser {
private:
    char* filename;
    int PRNCode;

public:
    /**
     * Constructor create RinexParser object.
     *
     * @param filename Path to Rinex file.
     * @param prnCode PRN code of satellite.
     */
    RinexParser(char* filename, int PRNCode);

    /**
     * Parse time when antenna receive signal from satellite.
     *
     * @return time when antenna receive signal from satellite.
     */
    std::vector<int> getTimeObs(void);

    /**
     * Parse Rinex navigation file and write time and coordinates in files.
     *
     *  @param filenameOut Path to output file with coordinates.
     *  @param filenameTimeOut Path to output file with time marks.
    */
    void getCoordinates(char *filenameOut, char *filenameTimeOut);

    /**
     * Get antenna position from a rinex file.
     *
     *  @return Tuple of name of satellite and position.
    */
    std::tuple<std::string, std::vector<double>>getAntennaPosition(void);

    /**
     * Get antenna position from a rinex file.
     *
     *  @param obsCode Observation code (C1C - pseudorange, L1C - Carrier Phase and etc., see docs rinex format).
     *  @return Map time and data for selected obsCode.
    */
    std::map<int, long double> getObservation(const std::string& obsCode);

    /**
     * Parse Rinex observation file and write time and data by code in files.
     *
     *  @param filenameOut Path to output file with observations.
     *  @param filenameTimeOut Path to output file with time marks.
     *  @param obsCode Observation code (C1C - pseudorange, L1C - Carrier Phase and etc., see docs rinex format).
    */
    void getObservation(const std::string& filenameOut, const std::string &filenameTimeOut, const std::string& obsCode);

    /**
     * Calculate and write first differences for observations in file.
     *
     *  @param secondSatObs RinexParser instance of second observations.
     *  @param filenameOut Name of output file where output data is store.
     *  @param obsCode Observation code (C1C - pseudorange, L1C - Carrier Phase and etc., see docs rinex format).
    */
    void getFirstDifferences(RinexParser secondSatObs, const std::string& filenameOut, const std::string& obsCode);


};


#endif //SATELLITE_RINEXPARSER_H
