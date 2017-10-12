#ifndef TRAINCONTROLLER_H
#define TRAINCONTROLLER_H

#include <string>
#include <memory>
#include <vector>

#include "DataReader.h"
#include "Station.h"
#include "Train.h"

using namespace std;

class TrainController
{
    string _trainsFile = "Trains.txt";
    string _trainStationsFile = "TrainStations.txt";
    unique_ptr<DataReader> _trainData;
    unique_ptr<DataReader> _trainStationData;
    vector<unique_ptr<Station>> _stations;
    vector<unique_ptr<Train>> _trains;
    vector<int> split(string&);
public:
    TrainController();
    ~TrainController();
    void processTrains();
    void processStations();
};

#endif // !TRAINCONTROLLER_H
