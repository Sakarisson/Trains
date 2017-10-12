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

using namespace std;

class Station
{
private:
    vector<unique_ptr<Train>> _trains;
    vector<unique_ptr<Car>> _carPool;
    string _name;
public:
    Station();
    Station(string);
    ~Station();
    unique_ptr<Car> removeFirst();
    unique_ptr<Car> removeAtIndex(int);
    void addToPool(int id, CarType type, int param0 = 0, int param1 = 0);
    void addToPool(unique_ptr<Car>&);
    void addTrain(unique_ptr<Train>&);
};

#endif // !STATION_H
