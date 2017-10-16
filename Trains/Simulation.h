#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <memory>
#include <vector>

#include "DataReader.h"
#include "Station.h"
#include "Train.h"

class Simulation
{
    string _trainsFile = "Trains.txt";
    string _trainStationsFile = "TrainStations.txt";
    unique_ptr<DataReader> _trainData;
    unique_ptr<DataReader> _trainStationData;
    vector<unique_ptr<Station>> _stations;
    vector<unique_ptr<Train>> _trainsInTransit;
    vector<string> splitBySpace(string&);
public:
    Simulation();
    ~Simulation();
    void processTrains();
    void processStations();
};

#endif // !SIMULATION_H
