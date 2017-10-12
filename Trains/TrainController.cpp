#include <regex>
#include <iostream>
#include <sstream>
#include <iterator>

#include "TrainController.h"


TrainController::TrainController() {
    _trainData = make_unique<DataReader>(_trainsFile);
    _trainStationData = make_unique<DataReader>(_trainStationsFile);
}


TrainController::~TrainController() {
    
}

void TrainController::processTrains() {
    for each (string line in _trainData->getLines()) {
        vector<string> data = splitBySpace(line);
        unique_ptr<Train> newTrain = make_unique<Train>(
            stoi(data[0]),
            data[1],
            data[2],
            data[3],
            data[4],
            stoi(data[5])
        );
        for (size_t i = 6; i < data.size(); ++i) {
            newTrain->requestCar(CarType(stoi(data[i])));
        }
        _trains.push_back(move(newTrain));
    }
}

void TrainController::processStations() {
    for each (string line in _trainStationData->getLines()) {
        string name = line.substr(0, line.find(" ")); // Name is anything before the first space
        vector<string> rawCarData;
        try {
            regex re("\(([^\)]+)\)"); // Get all data that is between two parentheses
            regex_iterator<string::iterator> rit(line.begin(), line.end(), re);
            regex_iterator<string::iterator> rend;

            while (rit != rend) { // Iterate through all regex matches
                string res = rit->str();
                res = res.substr(res.find("(") + 1); // Remove everything before and including starting parenthesis
                rawCarData.push_back(res);
                ++rit;
            }
        }
        catch (regex_error &e) {
            cout << e.what() << endl;
        }
        unique_ptr<Station> newStation = make_unique<Station>(name);
        for each (string d in rawCarData) {
            vector<string> values = splitBySpace(d);
            while (values.size() < 4) {
                values.push_back("0"); // Insert "0" values at end to avoid out of range errors
            }
            newStation->addToPool(
                stoi(values[0]), 
                CarType(stoi(values[1])), 
                stoi(values[2]), 
                stoi(values[3])
            );
        }
        _stations.push_back(move(newStation));
    }
}

vector<string> TrainController::splitBySpace(string& input) {
    vector<string> result;
    char delim = ' ';
    stringstream ss;
    ss.str(input);
    string item;
    while (getline(ss, item, delim)) {
        result.push_back(item);
    }
    return result;
}
