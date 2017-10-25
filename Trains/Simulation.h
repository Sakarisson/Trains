#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <memory>
#include <vector>
#include <queue>

#include "DataReader.h"
#include "Station.h"
#include "Event.h"
#include "UI.h"

class Train;
class Time;

// Priority queue of pointers to Event
// Sorted according to the next event, which will happen
typedef std::priority_queue<
    std::shared_ptr<Event>, 
    std::vector<std::shared_ptr<Event>>, 
    EventComparison
> EventQueue;

class Simulation
{
public:
    Simulation();    // Constructor
    ~Simulation();   // Destructor
    void run();

    // ----------------- GETTERS -----------------
    int getTime() const;
    std::string getTimeString() const;

    // ------------------ LOGIC ------------------
    void scheduleEvent(std::shared_ptr<Event>);
    void addTrainToTransit(std::unique_ptr<Train>&);
    std::unique_ptr<Train> removeTrainById(int&);
    std::shared_ptr<Station> getStation(std::string&);
private:
    // ------------- INTERNAL LOGIC -------------
    std::vector<std::string> splitBySpace(std::string&);
    void processTrains();
    void processStations();
    void processTrainMaps();
    bool processNextEvent();
private:
    // ----------- INTERNAL VARIABLES -----------
    Time _currentTime;
    std::string _trainsFile = "Trains.txt";
    std::string _trainStationsFile = "TrainStations.txt";
    std::string _trainMapFile = "TrainMap.txt";
    std::unique_ptr<DataReader> _trainData;
    std::unique_ptr<DataReader> _trainStationData;
    std::unique_ptr<DataReader> _trainMapData;
    std::vector<std::shared_ptr<Station>> _stations;
    std::vector<std::unique_ptr<Train>> _trainsInTransit;
    std::unique_ptr<UI> _ui;
    EventQueue _eventQueue;
};

#endif // !SIMULATION_H
