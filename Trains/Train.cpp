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
        _cars.push_back(make_shared<CoachCar>());
        break;
    case SLEEPINGCAR:
        _cars.push_back(make_shared<SleepingCar>());
        break;
    case OPENFREIGHTCAR:
        _cars.push_back(make_shared<OpenFreightCar>());
        break;
    case COVEREDFREIGHTCAR:
        _cars.push_back(make_shared<CoveredFreightCar>());
        break;
    default:
        return false;
        break;
    }
    return true;
}

vector<shared_ptr<Car>> Train::getCars() const {
    return _cars;
}
