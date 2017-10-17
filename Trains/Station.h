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

class Station
{
private:
    // ----------- INTERNAL VARIABLES -----------
    std::vector<std::unique_ptr<Train>> _trains;
    std::vector<std::unique_ptr<Car>> _carPool;
    std::string _name;

    // ------------- INTERNAL LOGIC -------------
    bool addCarToTrain(CarType, std::unique_ptr<Train>&);
    void eraseEmptyCars();
public:
    Station();
    Station(std::string);
    ~Station();
    // ----------------- GETTERS -----------------
    std::unique_ptr<Train>& getTrainById(int);
    std::string getName() const;

    // ------------------ LOGIC ------------------
    std::unique_ptr<Train> removeTrainById(int);
    void addCarToPool(int id, CarType type, int param0 = 0, int param1 = 0);
    void addCarToPool(std::unique_ptr<Car>&);
    void addTrain(std::unique_ptr<Train>&);
    bool assembleTrain(int);
};

#endif // !STATION_H
