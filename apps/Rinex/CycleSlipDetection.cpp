#include "CycleSlipDetection.h"

#include "../DiscCorr/DiscCorr.cpp"
#include "RinexParser.h"
#include "../SP3/SP3Parser.h"

CycleSlipDetection::CycleSlipDetection(char *rinexFile, char *sp3File, int PRNCode) {
    RinexParser rinex(rinexFile, PRNCode);
    SP3Parser sp3(sp3File, PRNCode);

    SatPass satellite();
}
