#include <regex>
#include <iostream>
#include <sstream>
#include <iterator>

#include "Simulation.h"
#include "Train.h"
#include "UI.h"
#include "Time.h"

using std::cout;
using std::endl;

Simulation::Simulation() {
    _trainData = std::make_unique<DataReader>(_trainsFile);
    _trainStationData = std::make_unique<DataReader>(_trainStationsFile);
    _trainMapData = std::make_unique<DataReader>(_trainMapFile);
    _currentTime = std::make_unique<Time>();
    _ui = std::make_unique<UI>();
    processStations();
    processTrains();
    processTrainMaps();
}


Simulation::~Simulation() {
    
}

void Simulation::run() {
    while(this->processNextEvent()) {}
}

// ------------- INTERNAL LOGIC -------------
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

void Simulation::processTrains() {
    if (_trainData->getLines().size() == 0) {
        throw std::range_error("TrainData.txt: File is empty!");
    }
    int lineCounter = 1;
    for each (std::string line in _trainData->getLines()) {
        std::vector<std::string> data = splitBySpace(line);
        if (data.size() < 7) {
            throw std::range_error("TrainData.txt line " + std::to_string(lineCounter) + ": Expected at least 7 pieces of data. Found " + std::to_string(data.size()));
        }
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
                std::shared_ptr<Event> assembleEvent = std::make_shared<AssembleEvent>(this, newTrain->getId(), s, newTrain->getScheduledDepartureTime()->getMinutes() - 30);
                s->addTrain(move(newTrain));
                scheduleEvent(assembleEvent);
                break;
            }
        }
        ++lineCounter;
    }
}

void Simulation::processStations() {
    if (_trainStationData->getLines().size() == 0) {
        throw std::range_error("TrainStations.txt: File is empty!");
    }
    int lineCounter = 1;
    for each (std::string line in _trainStationData->getLines()) {
        std::string name = line.substr(0, line.find(" ")); // Name is anything before the first space
        std::vector<std::string> rawCarData;
        std::regex re("\(([^\)]+)\)"); // Get all data that is between two parentheses
        std::regex_iterator<std::string::iterator> rit(line.begin(), line.end(), re);
        std::regex_iterator<std::string::iterator> rend;

        while (rit != rend) { // Iterate through all regex matches
            std::string res = rit->str();
            res = res.substr(res.find("(") + 1); // Remove everything before and including starting parenthesis
            rawCarData.push_back(res);
            ++rit;
        }
        std::shared_ptr<Station> newStation = std::make_shared<Station>(name);
        for each (std::string d in rawCarData) {
            std::vector<std::string> values = splitBySpace(d);
            while (values.size() < 4) {
                values.push_back("0"); // Insert "0" values at end to avoid out of range errors
            }
            if (values.size() < 4) { // Double check, throw error if false
                throw std::range_error("TrainStations.txt line " + std::to_string(lineCounter) + ": Expected 4 pieces of data. Found " + std::to_string(values.size()));
            }
            newStation->addCarToPool(
                stoi(values[0]), 
                CarType(stoi(values[1])), 
                stoi(values[2]), 
                stoi(values[3])
            );
        }
        _stations.push_back(newStation);
        ++lineCounter;
    }
}

void Simulation::processTrainMaps() {
    if (_trainMapData->getLines().size() == 0) {
        throw std::range_error("TrainStations.txt: File is empty!");
    }
    int lineCounter = 1;
    for each (std::string line in _trainMapData->getLines()) {
        std::vector<std::string> rawData = splitBySpace(line);
        if (rawData.size() != 3) {
            throw std::range_error("TrainMap.txt line " + std::to_string(lineCounter) + ": Expected 3 pieces of data. Found " + std::to_string(rawData.size()));
        }
        std::shared_ptr<Station> a = getStation(rawData[0]);
        std::shared_ptr<Station> b = getStation(rawData[1]);
        int distance = stoi(rawData[2]);
        if (a == nullptr || b == nullptr) {
            throw std::runtime_error("TrainStations.txt line " + std::to_string(lineCounter) + ": Invalid data");
        }
        a->addDistanceToStation(b->getName(), distance);
        b->addDistanceToStation(a->getName(), distance);
        ++lineCounter;
    }
}

bool Simulation::processNextEvent() {
    if (_currentTime->pastMidnight() && _trainsInTransit.size() <= 0) {
        return false;
    }
    std::shared_ptr<Event> nextEvent = _eventQueue.top();
    if (nextEvent == nullptr) {
        return false;
    }
    _eventQueue.pop();
    _currentTime.reset(new Time(nextEvent->getTime()->getMinutes()));
    nextEvent->processEvent();
    return true;
}

// ----------------- GETTERS -----------------
int Simulation::getTime() const {
    return _currentTime->getMinutes();
}

std::string Simulation::getTimeString() const {
    return _currentTime->getString();
}

void Simulation::scheduleEvent(std::shared_ptr<Event> e) {
    _eventQueue.push(e);
}

// ------------------ LOGIC ------------------
void Simulation::addTrainToTransit(std::unique_ptr<Train>& train) {
    _trainsInTransit.push_back(move(train));
}

std::unique_ptr<Train> Simulation::removeTrainById(int& id) {
    std::unique_ptr<Train> train;
    for (size_t i = 0; i < _trainsInTransit.size(); ++i) {
        if (_trainsInTransit[i]->getId() == id) {
            train = move(_trainsInTransit[i]);
            _trainsInTransit.erase(_trainsInTransit.begin() + i);
            break;
        }
    }
    return move(train);
}

std::shared_ptr<Station> Simulation::getStation(std::string& name) {
    auto it = find_if(_stations.begin(), _stations.end(), [name](std::shared_ptr<Station> &s) { return s->getName() == name; });
    if (it != _stations.end()) {
        return *it;
    }
    else {
        return nullptr;
    }
}
