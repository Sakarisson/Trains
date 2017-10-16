#ifndef EVENT_H
#define EVENT_H

#include <memory>
#include "Time.h"

// Forward declarations
class Simulation;
class Station;

// Abstract Event base class
class Event
{
protected:
    std::shared_ptr<Time> _time;
public:
    Event(Time time) : _time(std::make_shared<Time>(time)) {}
    virtual ~Event() {}
    std::shared_ptr<Time> getTime() const { return _time; }
    virtual void processEvent() = 0; // Pure virtual
};

// Used to compare to Events with respect to time
// From the example project, McSmack burgerbar
class EventComparison {
public:
    bool operator() (std::shared_ptr<Event>& left, std::shared_ptr<Event>& right) {
        return left->getTime()->getMinutes() > right->getTime()->getMinutes();
    }
};

class AssembleEvent : public Event {
protected:
    Simulation* _sim;
    std::shared_ptr<Station> _station;
    int _trainId;
public:
    AssembleEvent(Simulation* sim, int trainId, std::shared_ptr<Station> station, Time time)
        : Event(time), _sim(sim), _trainId(trainId), _station(station) {}

    virtual void processEvent();
};

class LeaveStationEvent : public Event {
protected:
public:
    LeaveStationEvent(int time) : Event(time) {}

    virtual void processEvent();
};

#endif // !EVENT_H
