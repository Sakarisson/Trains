#ifndef DISTANCE_H
#define DISTANCE_H

#include "Station.h"
#include <algorithm>
#include <memory>

class Distance {
private:
    std::shared_ptr<Station> _to;
    int _distance;
public:
    Distance(std::shared_ptr<Station> to, int distance)
        : _to(to), _distance(distance) {}
    int getDistance() const { return _distance; }
    std::string getStationName() const { return _to->getName(); }
};

class DistanceManager {
private:
    std::vector<std::unique_ptr<Distance>> _distances;
public:
    DistanceManager() {}
    void addDistance(std::shared_ptr<Station> to, int distance) {
        _distances.push_back(std::make_unique<Distance>(to, distance));
    }
    int getDistance(std::string station) {
        auto it = std::find_if(_distances.begin(), _distances.end(), [station](std::unique_ptr<Distance>& d) { return d->getStationName() == station; });
        if (it != _distances.end()) {
            return (*it)->getDistance();
        }
        else {
            return 0;
        }
    }
};

#endif // !DISTANCE_H
