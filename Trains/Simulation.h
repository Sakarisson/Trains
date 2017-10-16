#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <memory>
#include <vector>

#include "DataReader.h"
#include "Station.h"
#include "Train.h"

class Event;

class Simulation
{
private:
    std::string _trainsFile = "Trains.txt";
    std::string _trainStationsFile = "TrainStations.txt";
    std::unique_ptr<DataReader> _trainData;
    std::unique_ptr<DataReader> _trainStationData;
    std::vector<std::shared_ptr<Station>> _stations;
    std::vector<std::unique_ptr<Train>> _trainsInTransit;
    std::vector<std::string> splitBySpace(std::string&);
    void processTrains();
    void processStations();
public:
    Simulation();
    ~Simulation();
    void scheduleEvent(std::unique_ptr<Event>&);
};

#endif // !SIMULATION_H
