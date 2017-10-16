#include "Event.h"
#include "Simulation.h"
#include "Train.h"


void AssembleEvent::processEvent() {
    if (_station->assembleTrain(_trainId)) {
        // Leave station...
        std::unique_ptr<Event> leaveStation = std::make_unique<LeaveStationEvent>(_time.getMinutes() + 30);
        _sim->scheduleEvent(leaveStation);
    }
    else {
        // Try again in 10 minutes
        std::unique_ptr<Event> nextTry = std::make_unique<AssembleEvent>(_sim, _trainId, _station, _time.getMinutes() + 10);
        _sim->scheduleEvent(nextTry);
    }
}

void LeaveStationEvent::processEvent() {
    // Do leave station logic...
}
