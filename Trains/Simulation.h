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
    std::shared_ptr<Time> _currentTime;
    std::string _trainsFile = "Trains.txt";
    std::string _trainStationsFile = "TrainStations.txt";
    std::unique_ptr<DataReader> _trainData;
    std::unique_ptr<DataReader> _trainStationData;
    std::vector<std::shared_ptr<Station>> _stations;
    std::vector<std::unique_ptr<Train>> _trainsInTransit;

    std::priority_queue<std::shared_ptr<Event>, std::vector<std::shared_ptr<Event>>, EventComparison> _eventQueue;
    
    std::vector<std::string> splitBySpace(std::string&);
    void processTrains();
    void processStations();
    //bool processNextEvent();
public:
    Simulation();
    ~Simulation();
    void scheduleEvent(std::shared_ptr<Event>);
    int getTime() const;
    std::string getTimeString() const;
    void addTrainToTransit(std::unique_ptr<Train>&);
    bool processNextEvent();
};

#endif // !SIMULATION_H
