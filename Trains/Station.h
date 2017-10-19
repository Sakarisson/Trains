#ifndef STATION_H
#define STATION_H

#include <vector>
#include <memory>

#include "Train.h"

#include "CoachCar.h"
#include "SleepingCar.h"
#include "CoveredFreightCar.h"
#include "OpenFreightCar.h"
#include "ElectricalEngine.h"
#include "DieselEngine.h"

#include "Constants.h"

class DistanceManager;

class Station
{
public:
    Station();
    Station(std::string&);
    ~Station();

    // ----------------- GETTERS -----------------
    std::unique_ptr<Train>& getTrainById(int);
    std::string getName() const;
    int getDistanceToStation(std::string&) const;

    // ------------------ LOGIC ------------------
    std::unique_ptr<Train> removeTrainById(int&);
    void addCarToPool(int, CarType, int param0 = 0, int param1 = 0);
    void addCarToPool(std::unique_ptr<Car>&);
    void addTrain(std::unique_ptr<Train>&);
    void addDistanceToStation(std::string&, int&);
    bool assembleTrain(int&);
private:
    // ------------- INTERNAL LOGIC -------------
    bool addCarToTrain(CarType, std::unique_ptr<Train>&);
    void eraseEmptyCars();
private:
    // ----------- INTERNAL VARIABLES -----------
    std::vector<std::unique_ptr<Train>> _trains;
    std::vector<std::unique_ptr<Car>> _carPool;
    std::string _name;
    std::unique_ptr<DistanceManager> _distances;
};

#endif // !STATION_H
