#include <iostream>
#include <string>
#include <dirent.h>
#include <cstring>

#include "../app/sp3/SP3.h"
#include "../app/sp3/Projection.h"

using namespace gpstk;
using namespace std;

int main() {
    SP3 sp3("/Users/aleksandrdimov/Documents/master/satellite/input/igs20502.sp3", 1);
//    sp3.getCoordinates("/Users/aleksandrdimov/Documents/master/satellite/output/sp3_3.txt");

    ofstream file;
    file.open("/Users/aleksandrdimov/Documents/master/satellite/output/sp3_interp.txt", ios::out);

    for (int i = 0; i < 85500; i+=300) {
        cout << i << endl;
        Triple c = sp3.getInterpolatedPosition(i);
        file << setprecision(6) << i << "," << c[0]/1000 << "," << c[1]/1000 << "," << c[2]/1000 << endl;
    }

    return 0;
}