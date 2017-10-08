#ifndef TRAIN_H
#define TRAIN_H

#include <vector>
#include <memory>

#include "Car.h"

using namespace std;

class Train
{
private:
    vector<unique_ptr<Car>> _cars;
public:
    Train();
    ~Train();
    bool addCar(CarType type);
};

#endif // !TRAIN_H