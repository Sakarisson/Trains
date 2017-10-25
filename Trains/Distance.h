#ifndef DISTANCE_H
#define DISTANCE_H

#include "Station.h"
#include <algorithm>
#include <memory>

class Distance {
private:
    std::string _to;
    int _distance;
public:
    Distance(std::string to, int distance)
        : _to(to), _distance(distance) {}
    int getDistance() const { return _distance; }
    std::string getStationName() const { return _to; }
};

class DistanceManager {
private:
    std::vector<Distance> _distances;
public:
    DistanceManager() {}
    void addDistance(std::string to, int distance) {
        _distances.push_back(Distance(to, distance));
    }
    int getDistance(std::string station) {
        auto it = std::find_if(_distances.begin(), _distances.end(), [station](Distance& d) { return d.getStationName() == station; });
        if (it != _distances.end()) {
            return (*it).getDistance();
        }
        else {
            return 0;
        }
    }
};

#endif // !DISTANCE_H
