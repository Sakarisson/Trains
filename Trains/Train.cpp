#include "Train.h"

#include <vector>
#include <memory>

using namespace std;

Train::Train() {

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
void Train::addCar(CarType type) {
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
        break;
    }
}

// ------------------ TEMP -------------------------
vector<shared_ptr<Car>> Train::getCars() {
    return _cars;
}
