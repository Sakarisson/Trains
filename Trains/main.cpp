#include "Train.h"

#include <iostream>

using namespace std;

int main() {
    Train t;
    t.addCar(ELECTRICALENGINE);
    t.addCar(DIESELENGINE);
    t.addCar(COACHCAR);
    t.addCar(OPENFREIGHTCAR);
    t.addCar(COVEREDFREIGHTCAR);
    t.addCar(SLEEPINGCAR);
    for each (auto &c in t.getCars()) {
        cout <<
            "Type: " << c->getTypeString() << endl <<
            "Capacity: " << c->getCapacityString() << endl <<
            "Area: " << c->getArea() << endl <<
            "Number of beds: " << c->getNumberOfBeds() << endl <<
            "Has internet: " << c->hasInternet() << endl <<
            "Number of chairs: " << c->getNumberOfChairs() << endl <<
            "Energy consumption: " << c->getConsumptionString() << endl <<
            "----------------" << endl;
    }
    getchar();
    return 0;
}
