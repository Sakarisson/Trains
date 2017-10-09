#include "Train.h"

#include <vector>
#include <memory>

using namespace std;

Train::Train() {

}


Train::~Train() {

}

bool Train::addCar(CarType type) {
    switch (type) {
    case COACHCAR:
        _cars.push_back(make_unique<CoachCar>());
        break;
    case SLEEPINGCAR:
        _cars.push_back(make_unique<SleepingCar>());
        break;
    case OPENFREIGHTCAR:
        _cars.push_back(make_unique<OpenFreightCar>());
        break;
    case COVEREDFREIGHTCAR:
        _cars.push_back(make_unique<CoveredFreightCar>());
        break;
    default:
        return false;
        break;
    }
    return true;
}

vector<shared_ptr<Car>> Train::getCars() {
    return _cars;
}
