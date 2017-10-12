#ifndef TRAINCONTROLLER_H
#define TRAINCONTROLLER_H

#include <string>
#include <memory>
#include <vector>

#include "DataReader.h"

using namespace std;

class TrainController
{
    string _trainsFile = "Trains.txt";
    string _trainStationsFile = "TrainStations.txt";
    unique_ptr<DataReader> _trains;
    unique_ptr<DataReader> _trainStations;
public:
    TrainController();
    ~TrainController();
    vector<string> getTrains() const;
    vector<string> getStations() const;
};

#endif // !TRAINCONTROLLER_H
