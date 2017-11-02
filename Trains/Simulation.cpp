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
    _startTime = 0;
    _endTime = std::string("23:59");
    _interval = 10;
    _currentTime = _startTime;
    _lastInterval = _currentTime;
}


Simulation::~Simulation() {
    while (!_eventQueue.empty()) {
        _eventQueue.pop();
    }
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

std::string Simulation::getStartTimeString() const {
    return _startTime.getString();
}

std::string Simulation::getEndTimeString() const {
    return _endTime.getString();
}

int Simulation::getNumberOfEventsInQueue() const {
    return _eventQueue.size();
}

// ------------------ LOGIC ------------------
void Simulation::scheduleAssembleEvent(std::shared_ptr<Train> train, std::shared_ptr<Station> station, Time time) {
    std::shared_ptr<Event> assembleEvent = std::make_shared<AssembleEvent>(shared_from_this(), train, station, train->getScheduledDepartureTime()->getMinutes() - 30);
    scheduleEvent(assembleEvent);
}

void Simulation::scheduleEvent(std::shared_ptr<Event> e) {
    _eventQueue.push(e);
}

void Simulation::changeIntervalTime(Time& interval) {
    _interval = interval;
}

void Simulation::changeStartTime(Time& startTime) {
    _startTime = startTime;
}

void Simulation::changeEndTime(Time& endTime) {
    _endTime = endTime;
}

void Simulation::goToStart() {
    while (_currentTime < _startTime) {
        if (_eventQueue.top()->getTime() <= _startTime) {
            processNextEvent();
        }
        else {
            _currentTime = _startTime;
        }
    }
}

void Simulation::goToNextInterval() {
    while (_currentTime < _lastInterval + _interval) {
        if (_eventQueue.top()->getTime() <= _lastInterval + _interval) {
            if (!processNextEvent()) {
                return;
            }
        }
        else {
            _currentTime = _lastInterval + _interval;
            _lastInterval = _currentTime;
            break;
        }
    }
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
