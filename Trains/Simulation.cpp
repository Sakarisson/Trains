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

std::string Simulation::getStartTimeString() const {
    return _startTime.getString();
}

std::string Simulation::getEndTimeString() const {
    return _endTime.getString();
}

// ------------------ LOGIC ------------------
void Simulation::scheduleAssembleEvent(std::shared_ptr<Train> train, std::shared_ptr<Station> station, Time time) {
    std::shared_ptr<Event> assembleEvent = std::make_shared<AssembleEvent>(shared_from_this(), train, station, *train->getScheduledDepartureTime());
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

void Simulation::goToNextInterval() {
    
}

// ------------- INTERNAL LOGIC -------------
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
