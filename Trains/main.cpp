#include "Train.h"

#include <iostream>

using namespace std;

int main() {
    Train t;
    t.addCar(CarType(4), 154, 55);
    t.addCar(DIESELENGINE, 126, 82);
    t.addCar(COACHCAR, 6, 1);
    t.addCar(OPENFREIGHTCAR, 72, 13);
    t.addCar(COVEREDFREIGHTCAR, 66);
    t.addCar(SLEEPINGCAR, 12);
    for each (auto &c in t.getCars()) {
        cout <<
            "Type: " << c->getTypeString() << endl <<
            "Capacity: " << c->getCapacityString() << endl <<
            "Area: " << c->getArea() << endl <<
            "Number of beds: " << c->getNumberOfBeds() << endl <<
            "Has internet: " << c->hasInternet() << endl <<
            "Number of chairs: " << c->getNumberOfChairs() << endl <<
            "Max speed: " << c->getMaxSpeed() << " km/h" << endl <<
            "Energy consumption: " << c->getConsumptionString() << endl <<
            "----------------" << endl;
    }
    getchar();
    return 0;
}
