#include "Event.h"
#include "Simulation.h"
#include "Train.h"


void AssembleEvent::processEvent() {
    _time = _time * 2;
}
