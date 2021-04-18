#include <iostream>

#include "app/rinex/RinexObs.h"
#include "app/rinex/MovingAverage.h"


using namespace std;

int main() {
//    RinexObs rinex("/home/alex/CLionProjects/Satellite/test_files/adis0020.21o", 18);

    MovingAverage foo(3);

    int data[] = { 1, 2, 3, 4, 5, 5, 4, 3, 2, 1 };
    for (int * itr = data; itr < data + 10; itr++) {
        foo.add(*itr);
        cout << "Added " << *itr << " avg: " << foo.avg() << endl;
    }

    cout << endl;

    MovingAverage bar(3);
    int data1[] = { 1, 2, 3, 4, 5, 5, 4, 3, 2, 1 };
    for (int * itr = data1; itr < data1 + 10; itr++) {
        bar.add(*itr);
        cout << "Added " << *itr << " avg: " << bar.avg() << endl;
    }
}