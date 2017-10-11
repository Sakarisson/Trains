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

using namespace std;

class Station
{
private:
    vector<unique_ptr<Car>> _carPool;
public:
    Station();
    ~Station();
    unique_ptr<Car> removeFirst();
};

#endif // !STATION_H
