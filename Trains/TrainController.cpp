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

}

void TrainController::processStations() {
    for each (string line in _trainStationData->getLines()) {
        string name = line.substr(0, line.find(" ")); // Name is anything before the first space
        vector<string> rawCarData;
        try {
            regex re("\(([^\)]+)\)");
            regex_iterator<string::iterator> rit(line.begin(), line.end(), re);
            regex_iterator<string::iterator> rend;

            while (rit != rend) {
                string res = rit->str();
                res = res.substr(res.find("(") + 1);
                rawCarData.push_back(res);
                ++rit;
            }
        }
        catch (regex_error &e) {
            cout << e.what() << endl;
        }
        unique_ptr<Station> newStation = make_unique<Station>(name);
        for each (string d in rawCarData) {
            vector<int> values = split(d);
            newStation->addToPool(values[0], CarType(values[1]), values[2], values[3]);
        }
        _stations.push_back(move(newStation));
    }
}

vector<int> TrainController::split(string &input) {
    vector<int> result;
    char delim = ' ';
    stringstream ss;
    ss.str(input);
    string item;
    while (getline(ss, item, delim)) {
        result.push_back(stoi(item));
    }
    while (result.size() < 4) {
        result.push_back(0);
    }
    return result;
}
