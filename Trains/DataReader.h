#ifndef DATAREADER_H
#define DATAREADER_H

#include <string>
#include <fstream>

#include <iostream>

using namespace std;

class DataReader
{
private:
    string _trainsFileName = "Trains.txt";
    string _trainStationsFileName = "TrainStations.txt";
    ifstream _trainsFile;
    ifstream _trainStationsFile;
    void openFiles();
public:
    DataReader();
    ~DataReader();
};

#endif // !DATAREADER_H
