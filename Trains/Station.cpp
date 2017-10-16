#include "Station.h"

Station::Station() {

}

Station::Station(std::string name) {
    _name = name;
}


Station::~Station() {

}

std::unique_ptr<Car> Station::removeFirst() {
    if (_carPool.size() > 0) {
        std::unique_ptr<Car> first = move(_carPool[0]);
        _carPool.erase(_carPool.begin());
        return move(first);
    }
    else {
        return nullptr;
    }
}

std::unique_ptr<Car> Station::removeAtIndex(int i) {
    if (_carPool.size() > i) {
        std::unique_ptr<Car> c = move(_carPool[i]);
        _carPool.erase(_carPool.begin() + i);
        return move(c);
    }
    else {
        return nullptr;
    }
}

void Station::addToPool(int id, CarType type, int param0, int param1) {
    switch (type) {
    case COACHCAR:
        _carPool.push_back(std::make_unique<CoachCar>(id, param0, param1));
        break;
    case SLEEPINGCAR:
        _carPool.push_back(std::make_unique<SleepingCar>(id, param0));
        break;
    case OPENFREIGHTCAR:
        _carPool.push_back(std::make_unique<OpenFreightCar>(id, param0, param1));
        break;
    case COVEREDFREIGHTCAR:
        _carPool.push_back(std::make_unique<CoveredFreightCar>(id, param0));
        break;
    case ELECTRICALENGINE:
        _carPool.push_back(std::make_unique<ElectricalEngine>(id, param0, param1));
        break;
    case DIESELENGINE:
        _carPool.push_back(std::make_unique<DieselEngine>(id, param0, param1));
        break;
    default:
        break;
    }
}

void Station::addToPool(std::unique_ptr<Car>& car) {
    if (car != nullptr) {
        _carPool.push_back(move(car));
    }
}

void Station::addTrain(std::unique_ptr<Train>& train) {
    if (train != nullptr) {
        _trains.push_back(move(train));
    }
}

std::string Station::getName() const {
    return _name;
}
