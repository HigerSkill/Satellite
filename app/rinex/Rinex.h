#ifndef SATELLITE_RINEX_H
#define SATELLITE_RINEX_H

/**
 * Provides the ability to receive information stored for the specified (by PRN code) satellite.
 */
class Rinex {
public:
    char *filename;
    int PRNCode;

    /**
     * Constructor create RinexParser object.
     *
     * @param filename Path to Rinex the file.
     * @param PRNCode PRN code of the satellite.
     */
    RinexParser(char* filename, int PRNCode);

    /**
     * Check that `PRN` code exists for the observation code (L1, L2 and etc.)
     *
     * @param obsCode Path to Rinex the file.
     *
     * @return Does the PRN code exist or not
     */
    bool PRNCodeExists(const std::string& obsCode);

    /**
     * Get antenna name from a rinex file.
     *
     *  @return Name of the satellite and position.
     */
    std::string getAntennaName(void);

};


#endif //SATELLITE_RINEX_H
