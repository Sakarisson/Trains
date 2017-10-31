#include "World.h"
#include "Simulation.h"
#include "DataReader.h"
#include "Station.h"
#include "Train.h"
#include "Time.h"
#include "Distance.h"

#include <sstream>
#include <regex>

World::World() {
    
}


World::~World() {

}

// ------------- INTERNAL LOGIC -------------
std::vector<std::string> World::splitBySpace(std::string& input) {
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

void World::initialize(std::shared_ptr<Simulation> sim) {
    std::unique_ptr<DataReader> _trainData = std::make_unique<DataReader>("Trains.txt");
    std::unique_ptr<DataReader> _trainStationData = std::make_unique<DataReader>("TrainStations.txt");
    std::unique_ptr<DataReader> _trainMapData = std::make_unique<DataReader>("TrainMap.txt");

    // ---------- PROCESS STATIONS --------------------
    processStations(_trainStationData->getLines());
    processTrains(sim, _trainData->getLines());
    processTrainMaps(_trainMapData->getLines());
}

std::vector<std::shared_ptr<Station>> World::getAllStations() {
    return _stations;
}

void World::processStations(std::vector<std::string>& trainStationData) {
    if (trainStationData.size() == 0) {
        throw std::range_error("TrainStations.txt: File is empty!");
    }
    int lineCounter = 1;
    for each (std::string line in trainStationData) {
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

void World::processTrains(std::shared_ptr<Simulation> simulation, std::vector<std::string>& trainData) {
    if (trainData.size() == 0) {
        throw std::range_error("TrainData.txt: File is empty!");
    }
    int lineCounter = 1;
    for each (std::string line in trainData) {
        std::vector<std::string> data = splitBySpace(line);
        if (data.size() < 7) {
            throw std::range_error("TrainData.txt line " + std::to_string(lineCounter) + ": Expected at least 7 pieces of data. Found " + std::to_string(data.size()));
        }
        std::shared_ptr<Train> newTrain = std::make_shared<Train>(
            stoi(data[0]),
            data[1],
            getStation(data[2]),
            data[3],
            data[4],
            stoi(data[5])
            );
        for (size_t i = 6; i < data.size(); ++i) {
            newTrain->requestCar(CarType(stoi(data[i])));
        }
        for each (auto &s in _stations) {
            if (s->getName() == newTrain->getDepartureStation()) {
                std::shared_ptr<Event> assembleEvent = std::make_shared<AssembleEvent>(simulation, newTrain, s, newTrain->getScheduledDepartureTime()->getMinutes() - 30);
                s->addTrain(newTrain);
                _trains.push_back(newTrain);
                simulation->scheduleAssembleEvent(newTrain, s, newTrain->getScheduledDepartureTime()->getMinutes() - 30);
                break;
            }
        }
        ++lineCounter;
    }
}

void World::processTrainMaps(std::vector<std::string>& trainMapData) {
    _distanceManager = std::make_shared<DistanceManager>();
    if (trainMapData.size() == 0) {
        throw std::range_error("TrainStations.txt: File is empty!");
    }
    int lineCounter = 1;
    for each (std::string line in trainMapData) {
        std::vector<std::string> rawData = splitBySpace(line);
        if (rawData.size() != 3) {
            throw std::range_error("TrainMap.txt line " + std::to_string(lineCounter) + ": Expected 3 pieces of data. Found " + std::to_string(rawData.size()));
        }
        std::string a = rawData[0];
        std::string b = rawData[1];
        int distance = stoi(rawData[2]);
        _distanceManager->addDistance(a, b, distance);
        ++lineCounter;
    }
}

std::shared_ptr<Station> World::getStation(std::string station) {
    auto it = std::find_if(_stations.begin(), _stations.end(), [station](std::shared_ptr<Station>& s) { return s->getName() == station; });
    if (it != _stations.end()) {
        return *it;
    }
    else {
        return nullptr;
    }
}
