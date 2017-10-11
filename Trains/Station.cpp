#include "Station.h"



Station::Station() {
    _carPool.push_back(make_unique<CoachCar>(6, true));
    _carPool.push_back(make_unique<CoachCar>(6, true));
    _carPool.push_back(make_unique<CoachCar>(666, true));
    _carPool.push_back(make_unique<CoachCar>(6, true));
}


Station::~Station() {

}

unique_ptr<Car> Station::removeFirst() {
    if (_carPool.size() > 0) {
        unique_ptr<Car> first = move(_carPool[0]);
        _carPool.erase(_carPool.begin());
        return move(first);
    }
    else {
        return nullptr;
    }
}

unique_ptr<Car> Station::removeAtIndex(int i) {
    if (_carPool.size() > i) {
        unique_ptr<Car> c = move(_carPool[i]);
        _carPool.erase(_carPool.begin() + i);
        return move(c);
    }
    else {
        return nullptr;
    }
}

void Station::addToPool(CarType type, int param0, int param1) {
    switch (type) {
    case COACHCAR:
        _carPool.push_back(make_unique<CoachCar>(param0, param1));
        break;
    case SLEEPINGCAR:
        _carPool.push_back(make_unique<SleepingCar>(param0));
        break;
    case OPENFREIGHTCAR:
        _carPool.push_back(make_unique<OpenFreightCar>(param0, param1));
        break;
    case COVEREDFREIGHTCAR:
        _carPool.push_back(make_unique<CoveredFreightCar>(param0));
        break;
    case ELECTRICALENGINE:
        _carPool.push_back(make_unique<ElectricalEngine>(param0, param1));
        break;
    case DIESELENGINE:
        _carPool.push_back(make_unique<DieselEngine>(param0, param1));
        break;
    default:
        break;
    }
}

void Station::addToPool(unique_ptr<Car> &car) {
    if (car != nullptr) {
        _carPool.push_back(move(car));
    }
}
