#ifndef TRAIN_H
#define TRAIN_H

#include <vector>

#include "Car.h"

class Train
{
private:
    std::vector<Car> _cars;
public:
    Train();
    ~Train();
};

#endif // !TRAIN_H