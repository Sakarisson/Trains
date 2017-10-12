#include <vector>
#include <memory>

#include "Train.h"
#include "Constants.h"

#include "CoachCar.h"
#include "SleepingCar.h"
#include "CoveredFreightCar.h"
#include "OpenFreightCar.h"
#include "ElectricalEngine.h"
#include "DieselEngine.h"

using namespace std;

Train::Train() {

}

Train::Train(
    int id,
    string departureStation,
    string destinationStation,
    string departureTime,
    string destinationTime
) {
    _id = id;
    _departureStation = departureStation;
    _destinationStation = destinationStation;
    _departureTime = departureStation;
    _destinationTime = destinationTime;
}


Train::~Train() {

}

// -------- GETTERS --------
string Train::getTrainNumber() const {
    return _trainNumber;
}

string Train::getDepartureStation() const {
    return _departureStation;
}

string Train::getDepartureTime() const {
    return _departureTime;
}

string Train::getDestinationStation() const {
    return _destinationStation;
}

string Train::getDestinationTime() const {
    return _destinationTime;
}

TrainState Train::getCurrentState() const {
    return _currentState;
}

string Train::getCurrentStateString() const {
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

// -------- SETTERS --------
void Train::setTrainNumber(string trainNumber) {
    _trainNumber = trainNumber;
}

void Train::setDepartureStation(string departureStation) {
    _departureStation = departureStation;
}

void Train::setDepartureTime(string departureTime) {
    _departureTime = departureTime;
}

void Train::setDestinationStation(string destinationStation) {
    _destinationStation = destinationStation;
}

void Train::setDestinationTime(string destinationTime) {
    _destinationTime = destinationTime;
}

void Train::setCurrentState(TrainState currentState) {
    _currentState = currentState;
}

// --------- LOGIC ---------

/*
Create a new Car and add to Train
Possible to choose between all valid Cars
Possibility for 2 different parameters, which default to 0
*/
//void Train::addCar(CarType type, int param0, int param1) {
//    switch (type) {
//    case COACHCAR:
//        _cars.push_back(make_unique<CoachCar>(param0, param1));
//        break;
//    case SLEEPINGCAR:
//        _cars.push_back(make_unique<SleepingCar>(param0));
//        break;
//    case OPENFREIGHTCAR:
//        _cars.push_back(make_unique<OpenFreightCar>(param0, param1));
//        break;
//    case COVEREDFREIGHTCAR:
//        _cars.push_back(make_unique<CoveredFreightCar>(param0));
//        break;
//    case ELECTRICALENGINE:
//        _cars.push_back(make_unique<ElectricalEngine>(param0, param1));
//        break;
//    case DIESELENGINE:
//        _cars.push_back(make_unique<DieselEngine>(param0, param1));
//        break;
//    default:
//        break;
//    }
//}

/*
Move ownership of Car object to Train
Params:  unique_ptr<Car> passed by reference
Returns: void
*/
void Train::addCar(unique_ptr<Car> &car) {
    if (car != nullptr) {
        _cars.push_back(move(car));
    }
}

/*
Remove ownership of Car from Train
Params:  none
Returns: Unowned pointer to Car OR nullptr
*/
unique_ptr<Car> Train::detachFirstCar() {
    if (_cars.size() > 0) {
        unique_ptr<Car> first = move(_cars[0]);
        _cars.erase(_cars.begin());
        return move(first);
    }
    else {
        return nullptr;
    }
}
