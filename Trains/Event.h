#ifndef EVENT_H
#define EVENT_H

#include <memory>

// Forward declarations
class Simulation;
class Station;

// Abstract Event base class
class Event
{
protected:
    unsigned int _time = 0; // Minutes since midnight
public:
    Event(unsigned int time) : _time(time) {}
    virtual ~Event() {}
    unsigned int getTime() const { return _time; }
    virtual void processEvent() = 0; // Pure virtual
};

// Used to compare to Events with respect to time
// From the example project, McSmack burgerbar
class EventComparison {
public:
    bool operator() (Event* left, Event* right) {
        return left->getTime() > right->getTime();
    }
};

class AssembleEvent : public Event {
protected:
    Simulation* _sim;
    std::shared_ptr<Station> _station;
    int _trainId;
public:
    AssembleEvent(Simulation* sim, int trainId, std::shared_ptr<Station> station, int time)
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
