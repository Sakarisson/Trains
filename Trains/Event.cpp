#include "Event.h"
#include "Simulation.h"
#include "Train.h"

void AssembleEvent::processEvent() {
    if (_station->assembleTrain(_trainId)) {
        // Leave station in 30 minutes
        std::shared_ptr<Event> leaveStation = std::make_shared<GetReadyEvent>(_sim, _trainId, _station, _time->getMinutes() + 20);
        _sim->scheduleEvent(leaveStation);
    }
    else {
        // Try again in 10 minutes
        std::shared_ptr<Event> nextTry = std::make_shared<AssembleEvent>(_sim, _trainId, _station, _time->getMinutes() + 10);
        _sim->scheduleEvent(nextTry);
    }
}

void GetReadyEvent::processEvent() {
    _station->getTrainById(_trainId)->setCurrentState(READY);
    // Leave station in 10 minutes
    std::shared_ptr<Event> leaveStation = std::make_shared<LeaveStationEvent>(_sim, _trainId, _station, _time->getMinutes() + 10);
    _sim->scheduleEvent(leaveStation);
}

void LeaveStationEvent::processEvent() {
    // Do leave station logic
    auto t = _station->removeTrainById(_trainId);
    t->setCurrentState(RUNNING);
    _sim->addTrainToTransit(t);
}
