#include "Train.h"
#include "CoveredFreightCar.h"

#include "Station.h"
#include "TrainController.h"

#include <iostream>

using namespace std;

int main() {
    Train t;
    //t.addCar(CarType(4), 154, 55); // Electric engine - 4
    //t.addCar(DIESELENGINE, 126, 82);
    //t.addCar(COACHCAR, 6, true);
    //t.addCar(OPENFREIGHTCAR, 72, 13);
    //t.addCar(COVEREDFREIGHTCAR, 66);
    //t.addCar(SLEEPINGCAR, 12);
    t.setCurrentState(READY);
    Station s;
    unique_ptr<Car> c = s.removeAtIndex(2);
    t.addCar(c);
    s.addToPool(t.detachFirstCar());

    TrainController tc;
    for each (string line in tc.getStations()) {
        cout << line << endl;
    }

    return 0;
}
