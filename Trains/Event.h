#ifndef EVENT_H
#define EVENT_H

#include <memory>

// Forward declarations
class Simulation;
class Train; 

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
    bool operator() (Event * left, Event * right) {
        return left->getTime() > right->getTime();
    }
};

class AssembleEvent : public Event {
protected:
    std::shared_ptr<Simulation> _sim;
    std::shared_ptr<Train> _train;
public:
    AssembleEvent(std::shared_ptr<Simulation> sim, std::shared_ptr<Train> train, int time)
    : Event(time), _sim(sim), _train(train) {}

    virtual void processEvent();
};

#endif // !EVENT_H
