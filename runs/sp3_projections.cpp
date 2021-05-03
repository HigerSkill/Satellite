#include <iostream>
#include <string>
#include <dirent.h>
#include <cstring>

#include "../app/sp3/SP3.h"
#include "../app/sp3/Projection.h"

using namespace gpstk;
using namespace std;

int main() {

    const char *directory = "/home/alex/Downloads/sp3/";

    struct dirent *entry = nullptr;
    DIR *dp = nullptr;

    dp = opendir(directory);

    if (dp != nullptr) {
        int i = 0;
        dp = opendir(directory);
        while (entry = readdir(dp)) {
            if (i == 3) {
                break;
            }

            if ((string(entry->d_name).length() < 5)) {
                continue;
            }

            cout << "File № " << ++i << endl;

            string file = string(directory) + string(entry->d_name);
            char file_ar[file.length() + 1];
            strcpy(file_ar, file.c_str());

            for (int prn = 1; prn <= 1; prn++) {
                SP3 sp3(file_ar, prn);

                ConfigRun config{
                    prn,
                    "L1C",
                    32.77,
                    35.020,
                    4396111.1752,
                    3080477.641910,
                    3433499.46187
                }; // BSHM

                Projection projections(sp3, config.station);

                string filename =  "../output/projection_";
                filename = filename + to_string(prn) + ".txt";

                char file_out[filename.length() + 1];
                strcpy(file_out, filename.c_str());

                projections.getProjections(file_out);
            }
        }
    }

    closedir(dp);

    return 0;
}