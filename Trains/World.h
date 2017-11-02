#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include <string>

// Forward declarations
class Train;
class Station;
class DistanceManager;
class Simulation;

class World
{
public:
    World();
    ~World();
    void initialize(std::shared_ptr<Simulation>);
    std::vector<std::shared_ptr<Station>> getAllStations();
    std::shared_ptr<Station> getStation(std::string);
    std::vector<std::shared_ptr<Train>> getAllTrains();
private:
    std::vector<std::string> splitBySpace(std::string&);
    void processStations(std::vector<std::string>&);
    void processTrains(std::shared_ptr<Simulation>, std::vector<std::string>&);
    void processTrainMaps(std::vector<std::string>&);
private:
    std::vector<std::shared_ptr<Station>> _stations;
    std::vector<std::shared_ptr<Train>> _trains;
    std::shared_ptr<DistanceManager> _distanceManager;
};

#endif // !WORLD_H