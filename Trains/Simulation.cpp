#include <regex>
#include <iostream>
#include <sstream>
#include <iterator>

#include "Simulation.h"
#include "Train.h"
#include "Time.h"
#include "Station.h"

using std::cout;
using std::endl;

Simulation::Simulation() {
    _interval = 10;
}


Simulation::~Simulation() {

}

void Simulation::run() {
    while(this->processNextEvent()) {}
}

// ----------------- GETTERS -----------------
int Simulation::getTime() const {
    return _currentTime.getMinutes();
}

std::string Simulation::getTimeString() const {
    return _currentTime.getString();
}

std::string Simulation::getIntervalString() const {
    return _interval.getString();
}

std::shared_ptr<Station> Simulation::getStation(std::string& name) {
    auto it = find_if(_stations.begin(), _stations.end(), [name](std::shared_ptr<Station> &s) { return s->getName() == name; });
    if (it != _stations.end()) {
        return *it;
    }
    else {
        return nullptr;
    }
}

std::vector<std::shared_ptr<Station>> Simulation::getAllStations() {
    return _stations;
}

// ------------------ LOGIC ------------------
void Simulation::scheduleEvent(std::shared_ptr<Event> e) {
    _eventQueue.push(e);
}

void Simulation::addTrainToTransit(std::unique_ptr<Train>& train) {
    _trainsInTransit.push_back(move(train));
}

std::shared_ptr<Train> Simulation::removeTrainById(int& id) {
    std::unique_ptr<Train> train;
    for (size_t i = 0; i < _trainsInTransit.size(); ++i) {
        if (_trainsInTransit[i]->getId() == id) {
            train = move(_trainsInTransit[i]);
            _trainsInTransit.erase(_trainsInTransit.begin() + i);
            break;
        }
    }
    return move(train);
}

std::shared_ptr<Simulation> Simulation::pointerToThis() {
    return shared_from_this();
}

// ------------- INTERNAL LOGIC -------------
void Simulation::scheduleAssembleEvent(std::shared_ptr<Train> train, std::shared_ptr<Station> station, Time time) {
    std::shared_ptr<Event> assembleEvent = std::make_shared<AssembleEvent>(shared_from_this(), train, station, *train->getScheduledDepartureTime());
    scheduleEvent(assembleEvent);
}
bool Simulation::processNextEvent() {
    if (_currentTime.pastMidnight() && _trainsInTransit.size() <= 0) {
        return false;
    }
    std::shared_ptr<Event> nextEvent = _eventQueue.top();
    if (nextEvent == nullptr) {
        return false;
    }
    _eventQueue.pop();
    _currentTime = nextEvent->getTime();
    nextEvent->processEvent();
    return true;
}
