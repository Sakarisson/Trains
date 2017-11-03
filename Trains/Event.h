#ifndef EVENT_H
#define EVENT_H

#include <memory>
#include "Time.h"

// Forward declarations
class Simulation;
class Station;
class Train;

enum EventType {
    ASSEMBLE,
    GETREADY,
    LEAVESTATION,
    ARRIVE,
    DISASSEMBLE
};

// Abstract Event base class
class Event {
protected:
    Time _time;
    std::weak_ptr<Simulation> _sim;
    std::shared_ptr<Station> _station;
    std::shared_ptr<Train> _train;
public:
    Event(std::weak_ptr<Simulation> sim, std::shared_ptr<Train> train, std::shared_ptr<Station> station, Time time)
        : _sim(sim), _train(train), _station(station), _time(time) {}
    virtual ~Event() {}
    Time getTime() const;
    std::shared_ptr<Train> getTrain();
    std::shared_ptr<Station> getStation();
    virtual void processEvent() = 0; // Pure virtual
    virtual EventType getEventType() = 0;
    virtual std::string getEventTypeString() = 0;
};

// Used to compare to Events with respect to time
// From the example project, McSmack burgerbar
class EventComparison {
public:
    bool operator() (std::shared_ptr<Event>&, std::shared_ptr<Event>&);
};

class AssembleEvent : public Event {
public:
    AssembleEvent(std::weak_ptr<Simulation> sim, std::shared_ptr<Train> train, std::shared_ptr<Station> station, Time time)
        : Event(sim, train, station, time) {}

    void processEvent() override;
    EventType getEventType() override { return ASSEMBLE; }
    std::string getEventTypeString() override { return "Assemble"; }
};

class GetReadyEvent : public Event {
public:
    GetReadyEvent(std::weak_ptr<Simulation> sim, std::shared_ptr<Train> train, std::shared_ptr<Station> station, Time time)
        : Event(sim, train, station, time) {}

    void processEvent() override;
    EventType getEventType() override { return GETREADY; }
    std::string getEventTypeString() override { return "Get Ready"; }
};

class LeaveStationEvent : public Event {
public:
    LeaveStationEvent(std::weak_ptr<Simulation> sim, std::shared_ptr<Train> train, std::shared_ptr<Station> station, Time time)
        : Event(sim, train, station, time) {}

    void processEvent() override;
    EventType getEventType() override { return LEAVESTATION; }
    std::string getEventTypeString() override { return "Leave Station"; }
};

class ArriveEvent : public Event {
public:
    ArriveEvent(std::weak_ptr<Simulation> sim, std::shared_ptr<Train> train, std::shared_ptr<Station> station, Time time)
        : Event(sim, train, station, time) {}

    void processEvent() override;
    EventType getEventType() override { return ARRIVE; }
    std::string getEventTypeString() override { return "Arrive"; }
};

class DisassembleEvent : public Event {
public:
    DisassembleEvent(std::weak_ptr<Simulation> sim, std::shared_ptr<Train> train, std::shared_ptr<Station> station, Time time)
        : Event(sim, train, station, time) {}

    void processEvent() override;
    EventType getEventType() override { return DISASSEMBLE; }
    std::string getEventTypeString() override { return "Disassemble"; }
};

#endif // !EVENT_H
