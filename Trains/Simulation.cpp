#include <regex>
#include <iostream>
#include <sstream>
#include <iterator>

#include "Simulation.h"
#include "Event.h"

using std::cout;
using std::endl;

Simulation::Simulation() {
    _trainData = std::make_unique<DataReader>(_trainsFile);
    _trainStationData = std::make_unique<DataReader>(_trainStationsFile);
    processStations();
    processTrains();
}


Simulation::~Simulation() {
    
}

void Simulation::processTrains() {
    for each (std::string line in _trainData->getLines()) {
        std::vector<std::string> data = splitBySpace(line);
        std::unique_ptr<Train> newTrain = std::make_unique<Train>(
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
        for each (auto &s in _stations) {
            if (s->getName() == newTrain->getDepartureStation()) {
                s->addTrain(move(newTrain));
                break;
            }
        }
    }
}

void Simulation::processStations() {
    for each (std::string line in _trainStationData->getLines()) {
        std::string name = line.substr(0, line.find(" ")); // Name is anything before the first space
        std::vector<std::string> rawCarData;
        try {
            std::regex re("\(([^\)]+)\)"); // Get all data that is between two parentheses
            std::regex_iterator<std::string::iterator> rit(line.begin(), line.end(), re);
            std::regex_iterator<std::string::iterator> rend;

            while (rit != rend) { // Iterate through all regex matches
                std::string res = rit->str();
                res = res.substr(res.find("(") + 1); // Remove everything before and including starting parenthesis
                rawCarData.push_back(res);
                ++rit;
            }
        }
        catch (std::regex_error &e) {
            cout << e.what() << endl;
        }
        std::shared_ptr<Station> newStation = std::make_shared<Station>(name);
        for each (std::string d in rawCarData) {
            std::vector<std::string> values = splitBySpace(d);
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
        _stations.push_back(newStation);
    }
}

std::vector<std::string> Simulation::splitBySpace(std::string& input) {
    std::vector<std::string> result;
    char delim = ' ';
    std::stringstream ss;
    ss.str(input);
    std::string item;
    while (getline(ss, item, delim)) {
        result.push_back(item);
    }
    return result;
}

void Simulation::scheduleEvent(std::unique_ptr<Event>& e) {
    std::vector<std::unique_ptr<Event>> vec;
    vec.push_back(move(e));
}
