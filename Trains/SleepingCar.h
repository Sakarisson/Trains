#ifndef SLEEPINGCAR_H
#define SLEEPINGCAR_H

#include "PassengerCar.h"

class SleepingCar : public PassengerCar {
public:
    SleepingCar(int, int);
    virtual ~SleepingCar() {}

    // ----------------- GETTERS -----------------
    int getNumberOfBeds() const override;
    CarType getType() const override;
    std::string getTypeString() const override;

    std::string getInfo() const override;
private:
    int _numberOfBeds;
};

#endif // !SLEEPINGCAR_H
