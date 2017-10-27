#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <memory>
#include <vector>
#include <queue>

#include "DataReader.h"
#include "Event.h"

class Station;
class Train;
class Time;

// Priority queue of pointers to Event
// Sorted according to the next event, which will happen
typedef std::priority_queue<
    std::shared_ptr<Event>, 
    std::vector<std::shared_ptr<Event>>, 
    EventComparison
> EventQueue;

class Simulation : public std::enable_shared_from_this<Simulation>
{
public:
    Simulation();    // Constructor
    ~Simulation();   // Destructor
    void run();

    // ----------------- GETTERS -----------------
    int getTime() const;
    std::string getTimeString() const;
    std::string getIntervalString() const;
    //std::shared_ptr<Station> getStation(std::string&);
    //std::vector<std::shared_ptr<Station>> getAllStations();

    // ------------------ LOGIC ------------------
    void scheduleAssembleEvent(std::shared_ptr<Train>, std::shared_ptr<Station>, Time);
    void scheduleEvent(std::shared_ptr<Event>);
    //void addTrainToTransit(std::unique_ptr<Train>&);
    //std::shared_ptr<Train> removeTrainById(int&);
    //std::shared_ptr<Simulation> pointerToThis();
private:
    // ------------- INTERNAL LOGIC -------------
    bool processNextEvent();
private:
    // ----------- INTERNAL VARIABLES -----------
    Time _currentTime;
    Time _interval;
    std::vector<std::shared_ptr<Station>> _stations;
    std::vector<std::unique_ptr<Train>> _trainsInTransit;
    EventQueue _eventQueue;
};

#endif // !SIMULATION_H
