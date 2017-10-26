#ifndef DISTANCE_H
#define DISTANCE_H

#include <string>
#include <vector>
#include <memory>

class Distance {
public:
    Distance(std::string destination, int distance)
        : _destination(destination), _distance(distance) {}
    ~Distance() {}
    int getDistance() const;
    std::string getDestinationName() const;
private:
    std::string _destination;
    int _distance;
};

class StationMap {
public:
    StationMap(std::string name) : _name(name) {}
    ~StationMap() {}
    std::string getName() const;
    int getDistance(std::string&) const;
    void addDistance(std::string&, int&);
private:
    std::string _name;
    std::vector<Distance> _distances;
};

class DistanceManager {
public:
    DistanceManager() {}
    ~DistanceManager() {}

    void addDistance(std::string&, std::string&, int&);
    int getDistance(std::string&, std::string&) const;
private:
    std::vector<std::shared_ptr<StationMap>> _stations;
};

#endif // !DISTANCE_H
