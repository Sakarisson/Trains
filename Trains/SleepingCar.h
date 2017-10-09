#ifndef SLEEPINGCAR_H
#define SLEEPINGCAR_H

#include "PassengerCar.h"

class SleepingCar : public PassengerCar {
private:
    int _numberOfBeds = 0;
public:
    SleepingCar() {}
    ~SleepingCar() {}
    virtual int getNumberOfBeds() const{ return _numberOfBeds; }
};

#endif // !SLEEPINGCAR_H
