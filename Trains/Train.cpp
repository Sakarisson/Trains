#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

#include "World.h"

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

/*
 Default constructor
*/
Train::Train() {

}

/*
 Parameter constructor
*/
Train::Train(
    int id,
    std::string departureStation,
    std::shared_ptr<Station> destinationStation,
    Time departureTime,
    Time destinationTime,
    double maxSpeed,
    int travelDistance
) : _id(id), 
    _departureStation(departureStation),
    _destinationStation(destinationStation),
    _scheduledDepartureTime(std::make_unique<Time>(departureTime)),
    _expectedDepartureTime(std::make_unique<Time>(departureTime)),
    _scheduledDestinationTime(std::make_unique<Time>(destinationTime)),
    _expectedDestinationTime(std::make_unique<Time>(destinationTime)),
    _maxSpeed(maxSpeed),
    _travelDistance(travelDistance) {}


/*
 Destructor
*/
Train::~Train() {
    _destinationStation.reset();
}

// ----------------- GETTERS -----------------
// Times

/*
Get a reference to the scheduled departure time object
input:  void
output: std::unique_ptr<Time>&
*/
std::unique_ptr<Time>& Train::getScheduledDepartureTime() {
    return _scheduledDepartureTime;
}

/*
Get a reference to the scheduled destination time object
input:  void
output: std::unique_ptr<Time>&
*/
std::unique_ptr<Time>& Train::getScheduledDestinationTime() {
    return _scheduledDestinationTime;
}

/*
Get a reference to the expected departure time object
input:  void
output: std::unique_ptr<Time>&
*/
std::unique_ptr<Time>& Train::getExpectedDepartureTime() {
    return _expectedDepartureTime;
}

/*
 Get a reference to the expected destination time object
 input:  void
 output: std::unique_ptr<Time>&
*/
std::unique_ptr<Time>& Train::getExpectedDestinationTime() {
    return _expectedDestinationTime;
}

/*
 Get the destination station of the Train
 input:  void
 outpur: std::string
*/
std::string Train::getDestinationStation() const {
    if (auto dest = _destinationStation.lock()) {
        return dest->getName();
    }
    else {
        return "Could not find destination station";
    }
}

/*
 Get a pointer to the destination station
 Pointer because it's necessary to do some things with the destination station in an Event
 input:  void
 output: std::shared_ptr<Station>
*/
std::shared_ptr<Station> Train::getDestinationStationPointer() {
    if (auto dest = _destinationStation.lock()) {
        return dest;
    }
    else {
        return nullptr;
    }
}

/*
 Get the departure station of the Train
 input:  void
 output: std::string
*/
std::string Train::getDepartureStation() const {
    return _departureStation;
}

/*
 Get current State of Train
 input:  void
 output: TrainState
*/
TrainState Train::getCurrentState() const {
    return _currentState;
}

/*
 Get ID of train
 input:  void
 output: int
*/
int Train::getId() const {
    return _id;
}

/*
 Get a copy of the _missingCars vector
 input:  void
 output: std::vector<CarType>
*/
std::vector<CarType> Train::getMissingCars() {
    return _missingCars;
}

/*
 Get the current state of the Train as a string (as opposed to enum)
 input:  void
 output: std::string
*/
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

/*
 Tells whether or not Train has no attached cars
 input:  void
 return: bool
*/
bool Train::isEmpty() const {
    return _cars.size() == 0;
}

/*
 Get speed of running train
 input:  void
 output: double
*/
double Train::getSpeed() const {
    if (getCurrentState() != RUNNING) { // Return 0 km/h if train is not running
        return 0;
    }
    else {
        int depart = _expectedDepartureTime->getMinutes();
        int arrive = _expectedDestinationTime->getMinutes();
        double speed = (_travelDistance / double(arrive - depart)) * 60; // Calculate speed
        return speed;
    }
}

/*
 Calculate the max speed of train
 Takes into account the built-in max speed of the train and the max speed of its engines
 input:  void
 output: double
 */
double Train::getMaxSpeed() const {
    double maxSpeed = _maxSpeed;
    for each (auto& car in _cars) {
        if (car->getType() == ELECTRICALENGINE || car->getType() == DIESELENGINE) { // Only consider engines
            if (car->getMaxSpeed() < maxSpeed) { // If engine's speed is slower than current max
                maxSpeed = car->getMaxSpeed();
            }
        }
    }
    return maxSpeed;
}

// ----------------- SETTERS -----------------

/*
 Set state of Train
 input:  TrainState
 output: void
 */
void Train::setCurrentState(TrainState currentState) {
    _currentState = currentState;
}

// ------------------ LOGIC ------------------

/*
 Delay the train after failure to assemble
 input:  int&
 output: void
 */
void Train::delay(int& delayTime) {
    *_expectedDepartureTime += delayTime;
    *_expectedDestinationTime += delayTime;
}

/*
 Move ownership of Car object to Train
 input:  unique_ptr<Car> passed by reference
 output: void
*/
void Train::addCar(std::unique_ptr<Car> &car) {
    if (car != nullptr) {
        _cars.push_back(move(car));
    }
}

/*
 Add CarType to _missingCars vector
 input:  CarType
 output: void
*/
void Train::requestCar(CarType type) {
    _missingCars.push_back(type);
}

/*
 Remove ownership of Car from Train
 input:  void
 return: Unowned pointer to Car OR nullptr
*/
std::unique_ptr<Car> Train::detachFirstCar() {
    if (_cars.size() > 0) {
        std::unique_ptr<Car> first = move(_cars[0]); // move pointer to temp holder
        _cars.erase(_cars.begin()); // Erase now-empty pointer from vector
        return move(first); // Return ownership of pointer
    }
    else {
        return nullptr;
    }
}

/*
 Erase from _missingCars at given index
 input:  int&
 output: void
*/
void Train::eraseMissingCar(int& index) {
    if (_missingCars.size() > index) {
        _missingCars.erase(_missingCars.begin() + index);
    }
}

/*
 Print various details of the train, depending on the current LogLevel
 input:  LogLevel
 output: void
*/
void Train::print(LogLevel logLevel) const {
    int i = 0; // Car counter
    if (auto dest = _destinationStation.lock()) { // Lock weak_ptr
        cout <<
            "Train [" << std::to_string(_id) << "] (" << getCurrentStateString() << "), " <<
            "from " << _departureStation << " " << _scheduledDepartureTime->getString() << " (" << _expectedDepartureTime->getString() << ") " <<
            "to " << dest->getName() << " " << _scheduledDestinationTime->getString() << " (" << _expectedDestinationTime->getString() << ") " <<
            ", max speed = " << getMaxSpeed() << " km/h" << endl;
    }
    if (logLevel >= MEDIUM) { // Get medium log level info
        cout << "  Vehicles: (" << _cars.size() << ")" << endl;
        if (logLevel == HIGH) { // Get high log level info
            for each(auto &car in _cars) {
                cout << "    " << ++i << ": " << car->getInfo() << endl;
            }
        }
    }
}
