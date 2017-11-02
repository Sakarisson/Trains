#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

#include "Train.h"
#include "Station.h"
#include "Constants.h"

#include "CoachCar.h"
#include "SleepingCar.h"
#include "CoveredFreightCar.h"
#include "OpenFreightCar.h"
#include "ElectricalEngine.h"
#include "DieselEngine.h"

using std::cout;
using std::endl;

Train::Train() {

}

Train::Train(
    int id,
    std::string departureStation,
    std::shared_ptr<Station> destinationStation,
    Time departureTime,
    Time destinationTime,
    int maxSpeed
) : _id(id), 
    _departureStation(departureStation),
    _destinationStation(destinationStation),
    _scheduledDepartureTime(std::make_unique<Time>(departureTime)),
    _expectedDepartureTime(std::make_unique<Time>(departureTime)),
    _scheduledDestinationTime(std::make_unique<Time>(destinationTime)),
    _expectedDestinationTime(std::make_unique<Time>(destinationTime)),
    _maxSpeed(maxSpeed) {}


Train::~Train() {
    _destinationStation.reset();
}

// ----------------- GETTERS -----------------
// Times

std::unique_ptr<Time>& Train::getScheduledDepartureTime() {
    return _scheduledDepartureTime;
}

std::unique_ptr<Time>& Train::getScheduledDestinationTime() {
    return _scheduledDestinationTime;
}

std::unique_ptr<Time>& Train::getExpectedDepartureTime() {
    return _expectedDepartureTime;
}

std::unique_ptr<Time>& Train::getExpectedDestinationTime() {
    return _expectedDestinationTime;
}

std::string Train::getDestinationStation() const {
    if (auto dest = _destinationStation.lock()) {
        return dest->getName();
    }
}

std::shared_ptr<Station> Train::getDestinationStationPointer() {
    if (auto dest = _destinationStation.lock()) {
        return dest;
    }
}

std::string Train::getTrainNumber() const {
    return _trainNumber;
}

std::string Train::getDepartureStation() const {
    return _departureStation;
}

TrainState Train::getCurrentState() const {
    return _currentState;
}

int Train::getId() const {
    return _id;
}

std::vector<CarType> Train::getMissingCars() {
    return _missingCars;
}

std::string Train::getCurrentStateString() const {
    switch (_currentState) {
    case NOT_ASSEMBLED:
        return "Not assembled";
    case INCOMPLETE:
        return "Incomplete";
    case ASSEMBLED:
        return "Assembled";
    case READY:
        return "Ready";
    case RUNNING:
        return "Running";
    case ARRIVED:
        return "Arrived";
    case FINISHED:
        return "Finished";
    default:
        return "Unknown";
    }
}

std::vector<std::unique_ptr<Car>>& Train::getAllCars() {
    return _cars;
}

bool Train::isEmpty() const {
    return _cars.size() == 0;
}

// ----------------- SETTERS -----------------
void Train::setCurrentState(TrainState currentState) {
    _currentState = currentState;
}

// ------------------ LOGIC ------------------

void Train::delay(int& delayTime) {
    *_expectedDepartureTime += delayTime;
    *_expectedDestinationTime += delayTime;
}

/*
Move ownership of Car object to Train
Params:  unique_ptr<Car> passed by reference
Returns: void
*/
void Train::addCar(std::unique_ptr<Car> &car) {
    if (car != nullptr) {
        _cars.push_back(move(car));
    }
}

void Train::requestCar(CarType type) {
    _missingCars.push_back(type);
}

/*
Remove ownership of Car from Train
Params:  none
Returns: Unowned pointer to Car OR nullptr
*/
std::unique_ptr<Car> Train::detachFirstCar() {
    if (_cars.size() > 0) {
        std::unique_ptr<Car> first = move(_cars[0]);
        _cars.erase(_cars.begin());
        return move(first);
    }
    else {
        return nullptr;
    }
}

void Train::eraseMissingCar(int& index) {
    if (_missingCars.size() > index) {
        _missingCars.erase(_missingCars.begin() + index);
    }
}

void Train::print() const {
    int i = 0;
    if (auto dest = _destinationStation.lock()) {
        cout <<
            "Train [" << std::to_string(_id) << "] (" << getCurrentStateString() << "), " <<
            "from " << _departureStation << " " << _scheduledDepartureTime->getString() <<
            " to " << dest->getName() << " " << _scheduledDestinationTime->getString() << endl <<
            "  Vehicles: (" << _cars.size() << ")" << endl;
    }
    for each(auto &car in _cars) {
        cout << "    " << ++i << ": " << car->getInfo() << endl;
    }
}
