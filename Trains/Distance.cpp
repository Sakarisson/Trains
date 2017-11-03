#include "Distance.h"

#include <algorithm>

/*
 Get the actual integer distance
 input:  void
 output: int
*/
int Distance::getDistance() const {
    return _distance;
}

/*
 Get the name of destination
 input:  void
 output: std::string
*/
std::string Distance::getDestinationName() const {
    return _destination;
}

/*
 Get the name of the actual train station
 input:  void
 output: std::string
*/
std::string StationMap::getName() const {
    return _name;
}

/*
 Get distance from Station to other Station
 input:  std::string&
 output: int
*/
int StationMap::getDistance(std::string& other) const {
    for each (const Distance& d in _distances) {
        if (d.getDestinationName() == other) { // If other station found,
            return d.getDistance();            // Return distance to Station
        }
    }
    return -1; // Else return -1
}

/*
 Add Distance from Station to other station
 input:  std::string&, int&
 output: void
*/
void StationMap::addDistance(std::string& destination, int& distance) {
    _distances.push_back(Distance(destination, distance));
}

/*
 Add Distance between two locations
 input:  std::string&, std::string&, int&
 output: void
*/
void DistanceManager::addDistance(std::string& a, std::string& b, int& distance) {
    // Boolean variables to check if stations are currently accounted for in DistanceManager
    bool aFound = false;
    bool bFound = false;
    for each(std::shared_ptr<StationMap> m in _stations) {
        // Checks for station a and station b
        if (m->getName() == a) {
            m->addDistance(b, distance); // Add distance to b
            aFound = true;
        }
        else if (m->getName() == b) {
            m->addDistance(a, distance); // Add distance to a
            bFound = true;
        }
   }
    // If some station wasn't found, add that station to _stations
    if (!aFound) {
        std::shared_ptr<StationMap> a_map = std::make_unique<StationMap>(a);
        a_map->addDistance(b, distance);
        _stations.push_back(move(a_map));
    }
    if (!bFound) {
        std::shared_ptr<StationMap> b_map = std::make_unique<StationMap>(b);
        b_map->addDistance(a, distance);
        _stations.push_back(move(b_map));
    }
}

/*
 Get distance between two locations
 input:  std::string&, std::string&
 output: int
*/
int DistanceManager::getDistance(std::string& a, std::string& b) const {
    for each(std::shared_ptr<StationMap> m in _stations) { // Loop through Stations and return Distance to a or b when found
        if (m->getName() == a) {
            return m->getDistance(b);
        }
        if (m->getName() == b) {
            return m->getDistance(a);
        }
    }
}
