#include "Station.h"
#include <algorithm>    // std::find_if, remove_if

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

std::unique_ptr<Train>& Station::getTrainById(int id) {
    return *std::find_if(_trains.begin(), _trains.end(), [id](std::unique_ptr<Train>& t) { return t->getId() == id; });
}

std::unique_ptr<Train> Station::removeTrainById(int id) {
    std::unique_ptr<Train> train = nullptr;
    for (size_t i = 0; i < _trains.size(); ++i) {
        if (_trains[i]->getId() == id) {
            train = move(_trains[i]);
            _trains.erase(_trains.begin() + i);
            break;
        }
    }
    return train;
}

bool Station::addCarToTrain(CarType type, std::unique_ptr<Train>& train) {
    auto it = std::find_if(_carPool.begin(), _carPool.end(), [type](std::unique_ptr<Car> &c) { return c->getType() == type; });
    if (it == _carPool.end()) {
        return false;
    }
    else {
        train->addCar(move(*it));
        eraseEmptyCars();
        return true;
    }
}

void Station::eraseEmptyCars() {
    while (true) {
        for (size_t i = 0; i < _carPool.size(); ++i) {
            if (_carPool[i] == nullptr) {
                _carPool.erase(_carPool.begin() + i);
                break;
            }
        }
        return;
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

bool Station::assembleTrain(int trainId) {
    auto it = std::find_if(_trains.begin(), _trains.end(), [trainId](auto &t) { return t->getId() == trainId; });
    if (it == _trains.end()) {
        return false;
    }
    else {
        int i = 0;
        (*it)->setCurrentState(INCOMPLETE);
        for each (CarType request in (*it)->getMissingCars()) {
            if (addCarToTrain(request, (*it))) {
                (*it)->eraseMissingCar(i);
            }
            else {
                ++i;
            }
        }
        if ((*it)->getMissingCars().size() == 0) {
            (*it)->setCurrentState(ASSEMBLED);
            return true;
        }
        else {
            return false;
        }
    }
}

std::string Station::getName() const {
    return _name;
}
