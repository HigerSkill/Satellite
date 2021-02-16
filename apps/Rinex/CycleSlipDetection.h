//
// Created by alex on 2/12/21.
//

#ifndef SATELLITE_CYCLESLIPDETECTION_H
#define SATELLITE_CYCLESLIPDETECTION_H


class CycleSlipDetection {
private:
    char *rinexFile;
    char *sp3File;

    int PRNCode;

public:
    /**
     * Constructor create CycleSlipDetection object.
     *
     * @param rinexFile Path to Rinex file.
     * @param sp3File Path to SP3 file.
    */
    CycleSlipDetection(char* rinexFile, char* sp3File, int PRNCode);

};


#endif //SATELLITE_CYCLESLIPDETECTION_H
