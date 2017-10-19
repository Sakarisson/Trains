#include "Event.h"
#include "Simulation.h"
#include "Train.h"

std::shared_ptr<Time> Event::getTime() const {
    return _time;
}

bool EventComparison::operator() (std::shared_ptr<Event>& left, std::shared_ptr<Event>& right) {
    return left->getTime()->getMinutes() > right->getTime()->getMinutes();
}

void AssembleEvent::processEvent() {
    if (_station->assembleTrain(_trainId)) { // If train was fully assembled...
        // Leave station in 30 minutes
        std::shared_ptr<Event> getReady = std::make_shared<GetReadyEvent>(_sim, _trainId, _station, _time->getMinutes() + 20); // Schedule leaveStation event 20 minutes from now
        _sim->scheduleEvent(getReady);
    }
    else {
        // Try again in 10 minutes
        int delayTime = 10;
        _station->getTrainById(_trainId)->delay(delayTime);
        std::unique_ptr<Time> expectedDepartureTime = std::make_unique<Time>(_station->getTrainById(_trainId)->getExpectedDepartureTime()->getMinutes());
        std::shared_ptr<Event> nextTry = std::make_shared<AssembleEvent>(_sim, _trainId, _station, *expectedDepartureTime);
        _sim->scheduleEvent(nextTry);
    }
}

// Change trainState to READY 10 minutes before departure
void GetReadyEvent::processEvent() {
    _station->getTrainById(_trainId)->setCurrentState(READY);
    // Leave station in 10 minutes
    std::shared_ptr<Event> leaveStation = std::make_shared<LeaveStationEvent>(_sim, _trainId, _station, _time->getMinutes() + 10);
    _sim->scheduleEvent(leaveStation);
}

void LeaveStationEvent::processEvent() {
    // leave station logic
    auto t = _station->removeTrainById(_trainId);
    t->setCurrentState(RUNNING);
    Time arrivalTime = t->getScheduledDestinationTime()->getMinutes();
    _sim->addTrainToTransit(t);
    std::shared_ptr<Event> arrive = std::make_shared<ArriveEvent>(_sim, _trainId, arrivalTime);
    _sim->scheduleEvent(arrive);
}

void ArriveEvent::processEvent() {
    std::unique_ptr<Train> train = move(_sim->removeTrainById(_trainId));
    std::shared_ptr<Station> station = _sim->getStation(train->getDestinationStation());
    train->setCurrentState(ARRIVED);
    station->addTrain(train);
    std::shared_ptr<Event> disassemble = std::make_shared<DisassembleEvent>(_sim, _trainId, station, _time->getMinutes() + 20);
    _sim->scheduleEvent(disassemble);
}

void DisassembleEvent::processEvent() {
    while (!_station->getTrainById(_trainId)->isEmpty()) {
        auto car = move(_station->getTrainById(_trainId)->detachFirstCar());
        _station->addCarToPool(car);
    }
    _station->getTrainById(_trainId)->setCurrentState(FINISHED);
}
