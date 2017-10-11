#ifndef STATION_H
#define STATION_H

#include <vector>
#include <memory>

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
    vector<unique_ptr<Car>> _carPool;
    string _name;
    int _id;
public:
    Station();
    ~Station();
    unique_ptr<Car> removeFirst();
    unique_ptr<Car> removeAtIndex(int);
    void addToPool(CarType type, int param0 = 0, int param1 = 0);
    void addToPool(unique_ptr<Car>&);
};

#endif // !STATION_H
