#include "Train.h"

#include <iostream>

using namespace std;

int main() {
    Train t;
    t.addCar(COACHCAR);
    t.addCar(OPENFREIGHTCAR);
    t.addCar(COVEREDFREIGHTCAR);
    t.addCar(SLEEPINGCAR);
    for each (auto &c in t.getCars()) {
        cout <<
            "Capacity: " << c->getCapacityString() << endl <<
            "Capacity: " << c->getCapacityDouble() << endl <<
            "Number of beds: " << c->getNumberOfBeds() << endl <<
            "Has internet: " << c->hasInternet() << endl <<
            "Number of chairs: " << c->getNumberOfChairs() << endl <<
            "----------------" << endl;
    }
    getchar();
    return 0;
}
