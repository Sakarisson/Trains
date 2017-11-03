#include "Event.h"
#include "Simulation.h"
#include "Train.h"
#include "Station.h"

Time Event::getTime() const {
    return _time;
}

std::shared_ptr<Train> Event::getTrain() {
    return _train;
}

std::shared_ptr<Station> Event::getStation() {
    return _station;
}

bool EventComparison::operator() (std::shared_ptr<Event>& left, std::shared_ptr<Event>& right) {
    return left->getTime().getMinutes() > right->getTime().getMinutes();
}

void AssembleEvent::processEvent() {
    if (_station->assembleTrain(_train)) { // If train was fully assembled...
        // Leave station in 30 minutes
        std::shared_ptr<Event> getReady = std::make_shared<GetReadyEvent>(_sim, _train, _station, _time.getMinutes() + 20); // Schedule leaveStation event 20 minutes from now
        if (auto sim = _sim.lock()) {
            sim->scheduleEvent(getReady);
        }
    }
    else {
        // Try again in 10 minutes
        int delayTime = 10;
        _train->delay(delayTime);
        Time expectedDepartureTime = _train->getExpectedDepartureTime()->getMinutes();
        std::shared_ptr<Event> nextTry = std::make_shared<AssembleEvent>(_sim, _train, _station, expectedDepartureTime);
        if (auto sim = _sim.lock()) {
            sim->scheduleEvent(nextTry);
        }
    }
}

// Change trainState to READY 10 minutes before departure
void GetReadyEvent::processEvent() {
    _train->setCurrentState(READY);
    // Leave station in 10 minutes
    std::shared_ptr<Event> leaveStation = std::make_shared<LeaveStationEvent>(_sim, _train, _station, _time.getMinutes() + 10);
    if (auto sim = _sim.lock()) {
        sim->scheduleEvent(leaveStation);
    }
}

void LeaveStationEvent::processEvent() {
    // leave station logic
    _station->removeTrain(_train);
    _train->setCurrentState(RUNNING);
    Time arrivalTime = _train->getScheduledDestinationTime()->getMinutes();
    std::shared_ptr<Station> arrivalStation = _train->getDestinationStationPointer();
    std::shared_ptr<Event> arrive = std::make_shared<ArriveEvent>(_sim, _train, arrivalStation, arrivalTime);
    if (auto sim = _sim.lock()) {
        sim->scheduleEvent(arrive);
    }
}

void ArriveEvent::processEvent() {
    _train->setCurrentState(ARRIVED);
    _station->addTrain(_train);
    std::shared_ptr<Event> disassemble = std::make_shared<DisassembleEvent>(_sim, _train, _station, _time.getMinutes() + 20);
    if (auto sim = _sim.lock()) {
        sim->scheduleEvent(disassemble);
    }
}

void DisassembleEvent::processEvent() {
    while (!_train->isEmpty()) {
        auto car = move(_train->detachFirstCar());
        _station->addCarToPool(car);
    }
    _train->setCurrentState(FINISHED);
}
