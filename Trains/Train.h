#ifndef TRAIN_H
#define TRAIN_H

#include <vector>
#include <memory>

#include "Car.h"
#include "CoachCar.h"
#include "SleepingCar.h"
#include "CoveredFreightCar.h"
#include "OpenFreightCar.h"

using namespace std;

class Train
{
private:
    vector<shared_ptr<Car>> _cars;
public:
    Train();
    ~Train();
    bool addCar(CarType type);

    // TEMP TEST
    vector<shared_ptr<Car>> getCars() const;
};

#endif // !TRAIN_H