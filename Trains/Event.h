#pragma once
class Event
{
protected:
    unsigned int _time = 0;
public:
    Event();
    virtual ~Event();
    unsigned int getTime() const { return _time; }
    virtual void processEvent();
};

// Used to compare to Events with respect to time
// From the example project, McBurgerbar
class EventComparison {
public:
    bool operator() (Event * left, Event * right) {
        return left->getTime() > right->getTime();
    }
};
