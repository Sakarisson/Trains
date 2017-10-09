#include "Train.h"

#include <iostream>

using namespace std;

int main() {
    Train t;
    t.addCar(COACHCAR);
    t.addCar(OPENFREIGHTCAR);
    t.addCar(COVEREDFREIGHTCAR);
    t.addCar(SLEEPINGCAR);
    for each (auto c in t.getCars()) {
        cout <<
            c->getCapacityString() << endl <<
            c->getCapacityDouble() << endl <<
            c->getNumberOfBeds() << endl <<
            c->hasInternet() << endl <<
            c->getNumberOfChairs() << endl <<
            "----------------" << endl;
    }
    getchar();
    return 0;
}
