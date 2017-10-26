#ifndef EVENT_H
#define EVENT_H

#include <memory>
#include "Time.h"

// Forward declarations
class Simulation;
class Station;
class Train;

// Abstract Event base class
class Event
{
protected:
    Time _time;
public:
    Event(Time time) : _time(time) {}
    virtual ~Event() {}
    Time getTime() const;
    virtual void processEvent() = 0; // Pure virtual
};

// Used to compare to Events with respect to time
// From the example project, McSmack burgerbar
class EventComparison {
public:
    bool operator() (std::shared_ptr<Event>&, std::shared_ptr<Event>&);
};

class AssembleEvent : public Event {
protected:
    std::weak_ptr<Simulation> _sim;
    std::shared_ptr<Station> _station;
    std::shared_ptr<Train> _train;
public:
    AssembleEvent(std::weak_ptr<Simulation> sim, std::shared_ptr<Train> train, std::shared_ptr<Station> station, Time time)
        : Event(time), _sim(sim), _train(train), _station(station) {}

    virtual void processEvent();
};

class GetReadyEvent : public Event {
protected:
    std::weak_ptr<Simulation> _sim;
    std::shared_ptr<Station> _station;
    std::shared_ptr<Train> _train;
public:
    GetReadyEvent(std::weak_ptr<Simulation> sim, std::shared_ptr<Train> train, std::shared_ptr<Station> station, Time time)
        : Event(time), _sim(sim), _train(train), _station(station) {}

    virtual void processEvent();
};

class LeaveStationEvent : public Event {
protected:
    std::weak_ptr<Simulation> _sim;
    std::shared_ptr<Station> _station;
    std::shared_ptr<Train> _train;
public:
    LeaveStationEvent(std::weak_ptr<Simulation> sim, std::shared_ptr<Train> train, std::shared_ptr<Station> station, Time time)
        : Event(time), _sim(sim), _train(train), _station(station) {}

    virtual void processEvent();
};

class ArriveEvent : public Event {
protected:
    std::weak_ptr<Simulation> _sim;
    std::shared_ptr<Train> _train;
public:
    ArriveEvent(std::weak_ptr<Simulation> sim, std::shared_ptr<Train> train, Time time)
        : Event(time), _sim(sim), _train(train) {}

    virtual void processEvent();
};

class DisassembleEvent : public Event {
protected:
    std::weak_ptr<Simulation> _sim;
    std::shared_ptr<Station> _station;
    std::shared_ptr<Train> _train;
public:
    DisassembleEvent(std::weak_ptr<Simulation> sim, std::shared_ptr<Train> train, std::shared_ptr<Station> station, Time time)
        : Event(time), _sim(sim), _train(train), _station(station) {}

    virtual void processEvent();
};

#endif // !EVENT_H
