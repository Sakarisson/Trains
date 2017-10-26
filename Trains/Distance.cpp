#include "Distance.h"

#include <algorithm>

int Distance::getDistance() const {
    return _distance;
}

std::string Distance::getDestinationName() const {
    return _destination;
}

std::string StationMap::getName() const {
    return _name;
}

int StationMap::getDistance(std::string& other) const {
    for each(const Distance& d in _distances) {
        if (d.getDestinationName() == other) {
            return d.getDistance();
        }
    }
    return -1;
}

void StationMap::addDistance(std::string& destination, int& distance) {
    _distances.push_back(Distance(destination, distance));
}

void DistanceManager::addDistance(std::string& a, std::string& b, int& distance) {
    bool aFound = false;
    bool bFound = false;
    for each(std::shared_ptr<StationMap> m in _stations) {
        if (m->getName() == a) {
            m->addDistance(b, distance);
            aFound = true;
        }
        else if (m->getName() == b) {
            m->addDistance(a, distance);
            bFound = true;
        }
   }
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

int DistanceManager::getDistance(std::string& a, std::string& b) const {
    for each(std::shared_ptr<StationMap> m in _stations) {
        if (m->getName() == a) {
            return m->getDistance(b);
        }
        if (m->getName() == b) {
            return m->getDistance(a);
        }
    }
}
