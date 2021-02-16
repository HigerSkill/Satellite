#include <iostream>
#include <vector>
#include <string>

#include <singleton.hpp>
#include <Geomatics/DiscCorr.cpp>


using namespace std;

class Data : public Singleton<Data> {
public:
    vector<string> SP3_files;
    vector<string> Rinex_files;
};


int main() {
    GDCPass gd();
    d

    return 0;
}

