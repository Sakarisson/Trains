#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <memory>
#include <vector>
#include <queue>

#include "DataReader.h"
#include "Station.h"
#include "Train.h"
#include "Event.h"
#include "Time.h"

class Event;

class Simulation
{
private:
    // ----------- INTERNAL VARIABLES -----------
    std::shared_ptr<Time> _currentTime;
    std::string _trainsFile = "Trains.txt";
    std::string _trainStationsFile = "TrainStations.txt";
    std::string _trainMapFile = "TrainMap.txt";
    std::unique_ptr<DataReader> _trainData;
    std::unique_ptr<DataReader> _trainStationData;
    std::unique_ptr<DataReader> _trainMapData;
    std::vector<std::shared_ptr<Station>> _stations;
    std::vector<std::unique_ptr<Train>> _trainsInTransit;

    // Priority queue of pointers to Event
    // Sorted according to the next event, which will happen
    std::priority_queue<std::shared_ptr<Event>, std::vector<std::shared_ptr<Event>>, EventComparison> _eventQueue;
    
    // ------------- INTERNAL LOGIC -------------
    std::vector<std::string> splitBySpace(std::string&);
    void processTrains();
    void processStations();
    void processTrainMaps();
    bool processNextEvent();
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
    std::unique_ptr<Train> removeTrainById(int);
    std::shared_ptr<Station> getStation(std::string);
};

#endif // !SIMULATION_H
