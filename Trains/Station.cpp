#include "Station.h"
#include "Distance.h"
#include <algorithm>    // std::find_if, remove_if

Station::Station() {

}

Station::Station(std::string& name) {
    _name = name;
    _distances = std::make_unique<DistanceManager>();
}


Station::~Station() {

}

// ----------------- GETTERS -----------------
std::shared_ptr<Train> Station::getTrainById(int id) {
    return *std::find_if(_trains.begin(), _trains.end(), [id](const std::shared_ptr<Train> t) { return t->getId() == id; });
}

std::string Station::getName() const {
    return _name;
}

std::vector<std::unique_ptr<Car>>& Station::getAllCars() {
    return _carPool;
}

std::vector<std::shared_ptr<Train>> Station::getAllTrains() {
    return _trains;
}

// ------------------ LOGIC ------------------
void Station::removeTrain(std::shared_ptr<Train> train) {
    for (size_t i = 0; i < _trains.size(); ++i) {
        if (_trains[i] == train) {
            _trains.erase(_trains.begin() + i);
            break;
        }
    }
}

void Station::addCarToPool(int id, CarType type, int param0, int param1) {
    // Create car according to type and push back to _carPool
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
    _carPool.back()->addStationToHistory(this->getName()); // Add station to new car's history
}

void Station::addCarToPool(std::unique_ptr<Car>& car) {
    if (car != nullptr) {
        car->addStationToHistory(this->getName()); // Add station to car's history
        _carPool.push_back(move(car));
    }
}

void Station::addTrain(std::shared_ptr<Train> train) {
    if (train != nullptr) {
        _trains.push_back(train);
    }
}

bool Station::assembleTrain(int& trainId) {
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

bool Station::assembleTrain(std::shared_ptr<Train> train) {
    auto it = std::find_if(_trains.begin(), _trains.end(), [train](auto t) { return train == t; });
    if (it == _trains.end()) {
        return false;
    }
    else {
        int i = 0;
        train->setCurrentState(INCOMPLETE);
        for each (CarType request in (*it)->getMissingCars()) {
            if (addCarToTrain(request, train)) {
                train->eraseMissingCar(i);
            }
            else {
                ++i;
            }
        }
        if (train->getMissingCars().size() == 0) {
            train->setCurrentState(ASSEMBLED);
            return true;
        }
        else {
            return false;
        }
    }
}

// ------------- INTERNAL LOGIC -------------
bool Station::addCarToTrain(CarType type, std::shared_ptr<Train> train) {
    // Sort vector of cars before selecting the first one
    std::sort(_carPool.begin(), _carPool.end(),
        [](const std::unique_ptr<Car>& a, const std::unique_ptr<Car>& b){ 
        return a->getId() < b->getId(); 
    });

    // Find first car of wanted type
    auto it = std::find_if(_carPool.begin(), _carPool.end(), [type](const std::unique_ptr<Car> &c) { return c->getType() == type; });
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
