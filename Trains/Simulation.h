#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <memory>
#include <vector>
#include <queue>

#include "DataReader.h"
#include "Event.h"

class Train;
class Time;

// Priority queue of pointers to Event
// Sorted according to the next event, which will happen
typedef std::priority_queue<
    std::shared_ptr<Event>, 
    std::vector<std::shared_ptr<Event>>, 
    EventComparison
> EventQueue;

class Simulation : public std::enable_shared_from_this<Simulation> {
public:
    Simulation();    // Constructor
    ~Simulation();   // Destructor
    void run();

    // ----------------- GETTERS -----------------
    int getTime() const;
    std::string getTimeString() const;
    std::string getIntervalString() const;
    std::string getStartTimeString() const;
    std::string getEndTimeString() const;
    int getNumberOfEventsInQueue() const;

    // ------------------ LOGIC ------------------
    void scheduleAssembleEvent(std::shared_ptr<Train>, std::shared_ptr<Station>, Time);
    void scheduleEvent(std::shared_ptr<Event>);
    void changeIntervalTime(Time&);
    void changeStartTime(Time&);
    void changeEndTime(Time&);
    void goToStart();
    void goToNextInterval();
    bool processNextEvent();
private:
    // ----------- INTERNAL VARIABLES -----------
    Time _startTime;
    Time _endTime;
    Time _currentTime;
    Time _interval;
    Time _lastInterval;
    std::vector<std::shared_ptr<Train>> _trainsInTransit;
    EventQueue _eventQueue;
};

#endif // !SIMULATION_H
